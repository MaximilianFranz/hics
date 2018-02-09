/*
 * Helpful links to understand im2col:
 * https://petewarden.com/2015/04/20/why-gemm-is-at-the-heart-of-deep-learning/
 * http://cs231n.github.io/convolutional-networks/
 * https://github.com/BVLC/caffe
 */

#include <cstring>
#include <algorithm>
#include "im2col.h"

namespace helper {

    void multiply_matrices_using_1d_vectors(const float *matrix_left,
                                            const int matrix_left_rows, const int matrix_left_columns,
                                            const float *matrix_right,
                                            const int matrix_right_rows, const int matrix_right_columns,
                                            float *result_matrix) {
        const auto result_matrix_columns = matrix_right_columns;
        for (int m = 0; m < matrix_left_rows; m++) {
            for (int n = 0; n < matrix_right_columns; n++) {
                float value = 0.f;
                for (int k = 0; k < matrix_right_rows; k++) {
                    value += matrix_left[m * matrix_left_columns + k] * matrix_right[k * matrix_right_columns + n];
                }
                result_matrix[m * result_matrix_columns + n] = value;
            }
        }
    }

    float *transpose_and_pad(int pad, int sizeX, int sizeY, float* input) {
        int newX = sizeX;
        int newY = sizeY;

        if (sizeX % pad != 0) {
            newY = ((sizeX / pad) + 1) * pad;
        }
        if (sizeY % pad != 0) {
            newX = ((sizeY / pad) + 1) * pad;
        }

        float* out = (float*)malloc(newX*newY*sizeof(float*));
        memset(out, 0, newX*newY*sizeof(float));


        for (int y = 0; y < sizeY; y++) {
            for (int x = 0; x < sizeX; x++) {
                float val = input[y*sizeX + x];
                int index = x * newX + y;
                out[index] = val;
            }
        }

        return out;

    };


    /**
    * Checks if a given index lies in the interval [0,boundary).
    *
    * The use case for this method is to check whether a row/column of a matrix is within the boundaries of an image
    * or whether the value of the element in the row/column is zero due to zero-padding.
    *
    * @param index      the index of a row/column of an image (2D matrix)
    * @param boundary   is a positive value
    * @return true      if value is in [0,boundary), false if not.
    */
    inline bool is_value_ge_zero_and_value_lt_boundary(int index, int boundary) {
        /*
         * casting from int to unsigned because we then need to check only one condition instead of two.
         * The boundary parameter is of type signed and is always positive, therefore its value is always lower than 0x800
         * casting a negative value of a parameter converts it to value higher than 0x800
         * thus checking value < boundary is sufficient
         */
        return static_cast<unsigned>(index) < static_cast<unsigned>(boundary);
    }

    template<typename Dtype>
    void set(const int object_size, const Dtype fill_byte, Dtype *object_to_fill) {
        if (fill_byte == 0) {
            std::memset(object_to_fill, 0, sizeof(Dtype) * object_size);
            return;
        }
        for (int i = 0; i < object_size; ++i) {
            object_to_fill[i] = fill_byte;
        }
    }

    // Explicit instantiation
    template void set<float>(const int object_size, const float fill_byte, float *object_to_fill);

    template void set<double>(const int object_size, const double fill_byte, double *object_to_fill);

    /*
     * Example:
     * Image 3x3, Kernel 2x2, Padding = 0, Stride = 1
     * Image:
     * 1 2 3
     * 4 5 6
     * 7 8 9
     *
     * 4 possible Filter positions for 2x2 Filter with no Padding
     * top-left quadrant:
     * 1 2
     * 4 5
     * is written as 1 2 4 5
     * top-right quadrant:
     * 2 3
     * 5 6
     * is written as 2 3 5 6
     * etc.
     *
     * Results in following outcome:
     * 1 2 4 5
     * 2 3 5 6
     * 4 5 7 8
     * 5 6 8 9
     *
     * Four to the right because: Kernel 2x2x1 = 4
     * Four to the bottom because: ((3-2+2*0)/1+1)^2 = 2*2 = 4
     *
     * Another Example:
     * input image is 227x227x3
     * Kernel is 11x11x3
     * stride is 4
     *
     * 363 to the right because 11*11*3
     * 3025 to the bottom because ((227-11)/4+1)^2 = 55*55 = 3025
     * => M = 3025x363
     *
     * Then perform Matrix multiply: M x W
     * where Weight Matrix W = 363x96
     */
    template<typename Dtype>
    void im2col_cpu(const Dtype *data_image, const int channels, const int height, const int width,
                    const int kernel_size, const int padding, const int stride,
                    Dtype *data_column) {

        const int output_h = (height - kernel_size + 2 * padding) / stride + 1;
        const int output_w = (height - kernel_size + 2 * padding) / stride + 1;

        // remember the amount of elements inside a channel to move the pointer forward by that many addresses
        const int channel_size = height * width;
        for (int channel = channels; channel--; data_image += channel_size) {
            for (int kernel_row = 0; kernel_row < kernel_size; kernel_row++) {
                for (int kernel_col = 0; kernel_col < kernel_size; kernel_col++) {

                    int input_row = -padding + kernel_row;

                    for (int output_rows = output_h; output_rows; output_rows--) {
                        if (!is_value_ge_zero_and_value_lt_boundary(input_row, height)) {
                            for (int output_cols = output_w; output_cols; output_cols--) {
                                *(data_column++) = 0;
                            }
                        } else {
                            int input_col = -padding + kernel_col;
                            for (int output_col = output_w; output_col; output_col--) {
                                if (is_value_ge_zero_and_value_lt_boundary(input_col, width)) {
                                    *(data_column++) = data_image[input_row * width + input_col];
                                } else {
                                    *(data_column++) = 0;
                                }
                                input_col += stride;
                            }
                        }
                        input_row += stride;
                    }

                }
            }
        }
    }

    // Explicit instantiation
    template void im2col_cpu<float>(const float *data_image, const int channels, const int height, const int width,
                                    const int kernel_size, const int padding, const int stride,
                                    float *data_column);

    template void im2col_cpu<double>(const double *data_image, const int channels, const int height, const int width,
                                     const int kernel_size, const int padding, const int stride,
                                     double *data_column);


    template<typename Dtype>
    void col2im_cpu(const Dtype *data_column, const int channels, const int height, const int width,
                    const int kernel_size, const int padding, const int stride,
                    Dtype *data_image) {

        set(height * width * channels, Dtype(0), data_image);

        const int output_h = (height - kernel_size + 2 * padding) / stride + 1;
        const int output_w = (height - kernel_size + 2 * padding) / stride + 1;

        // remember the amount of elements inside a channel to move the pointer forward by that many addresses
        const int channel_size = height * width;
        for (int channel = channels; channel--; data_image += channel_size) {
            for (int kernel_row = 0; kernel_row < kernel_size; kernel_row++) {
                for (int kernel_col = 0; kernel_col < kernel_size; kernel_col++) {

                    int input_row = -padding + kernel_row;

                    for (int output_row = 0; output_row < output_h; ++output_row) {
                        if (!is_value_ge_zero_and_value_lt_boundary(input_row, height)) {
                            data_column += output_w;
                        } else {
                            int input_col = -padding + kernel_col;

                            for (int output_col = 0; output_col < output_w; ++output_col) {
                                if (is_value_ge_zero_and_value_lt_boundary(input_col, width)) {
                                    data_image[input_row * width + input_col] += *data_column;
                                }
                                data_column++;
                                input_col += stride;
                            }
                        }
                        input_row += stride;
                    }

                }
            }
        }
    }

    // Explicit instantiation
    template void col2im_cpu<float>(const float *data_column, const int channels, const int height, const int width,
                                    const int kernel_size, const int padding, const int stride,
                                    float *data_image);

    template void col2im_cpu<double>(const double *data_column, const int channels, const int height, const int width,
                                     const int kernel_size, const int padding, const int stride,
                                     double *data_image);


    template<typename Dtype>
    void im2col_simple_version_cpu(const Dtype *data_image, const int channels, const int height, const int width,
                                   const int kernel_size, const int padding, const int stride,
                                   Dtype *data_column) {

        int kernel_h, kernel_w;
        kernel_h = kernel_w = kernel_size;

        int pad_h, pad_w;
        pad_h = pad_w = padding;

        int stride_h, stride_w;
        stride_h = stride_w = stride;

        const int output_h = (height - kernel_h + 2 * pad_h) / stride_h + 1;
        const int output_w = (height - kernel_w + 2 * pad_w) / stride_w + 1;
        int channels_col = channels * kernel_size * kernel_size;

        for (int c = 0; c < channels_col; ++c) {
            int w_offset = c % kernel_w;
            int h_offset = (c / kernel_w) % kernel_h;
            int c_im = c / (kernel_h * kernel_w);

            for (int h = 0; h < output_h; ++h) {
                for (int w = 0; w < output_w; ++w) {
                    int h_pad = h * stride_h - pad_h + h_offset;
                    int w_pad = w * stride_w - pad_w + w_offset;
                    if (h_pad >= 0 && h_pad < height && w_pad >= 0 && w_pad < width) {
                        data_column[(c * output_h + h) * output_w + w] =
                                data_image[(c_im * height + h_pad) * width + w_pad];
                    } else {
                        data_column[(c * output_h + h) * output_w + w] = 0;
                    }
                }
            }
        }
    }

    // Explicit instantiation
    template void
    im2col_simple_version_cpu<float>(const float *data_image, const int channels, const int height, const int width,
                                     const int kernel_size, const int padding, const int stride,
                                     float *data_column);

    template void
    im2col_simple_version_cpu<double>(const double *data_image, const int channels, const int height, const int width,
                                      const int kernel_size, const int padding, const int stride,
                                      double *data_column);


    template<typename Dtype>
    void col2im_simple_version_cpu(const Dtype *data_column, const int channels, const int height, const int width,
                                   const int kernel_size, const int padding, const int stride,
                                   Dtype *data_image) {
        int kernel_h, kernel_w;
        kernel_h = kernel_w = kernel_size;

        int pad_h, pad_w;
        pad_h = pad_w = padding;

        int stride_h, stride_w;
        stride_h = stride_w = stride;

        int height_col = (height - kernel_h + 2 * pad_h) / stride_h + 1;
        int width_col = (width - kernel_w + 2 * pad_w) / stride_w + 1;
        int channels_col = kernel_h * kernel_w * channels;

        std::fill(data_image, data_image + width * height * channels, 0);
        for (int c = 0; c < channels_col; ++c) {
            int w_offset = c % kernel_w;
            int h_offset = (c / kernel_w) % kernel_h;
            int c_im = c / (kernel_h * kernel_w);

            for (int h = 0; h < height_col; ++h) {
                for (int w = 0; w < width_col; ++w) {
                    int h_pad = h * stride_h - pad_h + h_offset;
                    int w_pad = w * stride_w - pad_w + w_offset;
                    if (h_pad >= 0 && h_pad < height && w_pad >= 0 && w_pad < width) {
                        data_image[(c_im * height + h_pad) * width + w_pad] +=
                                data_column[(c * height_col + h) * width_col + w];
                    }
                }
            }
        }
    }

    template<typename Dtype>
    void add_bias(Dtype *data_matrix, const Dtype *bias, int rows, int columns) {
        for (int row = 0; row < rows; row++) {
            for (int column = 0; column < columns; column++) {
                data_matrix[row * columns + column] = data_matrix[row * columns + column] + bias[row];
            }
        }
    }

    template void
    add_bias<float>(float *data_matrix, const float *bias, int rows, int columns);


    // Explicit instantiation
    template void
    col2im_simple_version_cpu<float>(const float *data_column, const int channels, const int height, const int width,
                                     const int kernel_size, const int padding, const int stride,
                                     float *data_image);

    template void
    col2im_simple_version_cpu<double>(const double *data_column, const int channels, const int height, const int width,
                                      const int kernel_size, const int padding, const int stride,
                                      double *data_image);
}
