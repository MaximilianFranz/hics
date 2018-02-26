/* Copyright 2018 The HICS Authors
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall
 * be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 */

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

    float *add_padding(int padding, int sizeX, int sizeY, const float *input, int *newX, int *newY) {
        int paddedX = sizeX;
        int paddedY = sizeY;

        if (sizeX % padding != 0) {
            paddedX = ((sizeX / padding) + 1) * padding;
        }
        if (sizeY % padding != 0) {
            paddedY = ((sizeY / padding) + 1) * padding;
        }

        float* out = new float [paddedX*paddedY];
        memset(out, 0, paddedX*paddedY*sizeof(float));

        float *dest = out;
        const float *src = input;
        for (int i = 0; i < sizeY; i++) {
            memcpy(dest, src, sizeX*sizeof(float));
            dest += paddedX;
            src += sizeX;
        }

        *newX = paddedX;
        *newY = paddedY;
        return out;
    }

    float *remove_padding(int padding, int sizeX, int sizeY, const float *input) {
        int paddedX = sizeX;

        if (sizeX % padding != 0) {
            paddedX = ((sizeX / padding) + 1) * padding;
        }


        float* out = new float[sizeX*sizeY];

        float *dest = out;
        const float *src = input;
        for (int i = 0; i < sizeY; i++) {
            memcpy(dest, src, sizeX*sizeof(float));
            dest += sizeX;
            src += paddedX;
        }

        return out;
    }

    template<typename Dtype>
    void im2col_cpu(const Dtype *data_image, const int channels, const int height, const int width,
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
    im2col_cpu<float>(const float *data_image, const int channels, const int height, const int width,
                      const int kernel_size, const int padding, const int stride,
                      float *data_column);

    template<typename Dtype>
    void col2im_cpu(const Dtype *data_column, const int channels, const int height, const int width,
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
        for (int channel = 0; channel < channels_col; ++channel) {
            int w_offset = channel % kernel_w;
            int h_offset = (channel / kernel_w) % kernel_h;
            int c_im = channel / (kernel_h * kernel_w);

            for (int h = 0; h < height_col; ++h) {
                for (int w = 0; w < width_col; ++w) {
                    int h_pad = h * stride_h - pad_h + h_offset;
                    int w_pad = w * stride_w - pad_w + w_offset;
                    if (h_pad >= 0 && h_pad < height && w_pad >= 0 && w_pad < width) {
                        data_image[(c_im * height + h_pad) * width + w_pad] +=
                                data_column[(channel * height_col + h) * width_col + w];
                    }
                }
            }
        }
    }

    // Explicit instantiation
    template void
    col2im_cpu<float>(const float *data_column, const int channels, const int height, const int width,
                      const int kernel_size, const int padding, const int stride,
                      float *data_image);

    template<typename Dtype>
    void add_bias(Dtype *data_matrix, const Dtype *bias, int rows, int columns) {
        for (int row = 0; row < rows; row++) {
            for (int column = 0; column < columns; column++) {
                data_matrix[row * columns + column] = data_matrix[row * columns + column] + bias[row];
            }
        }
    }

    // Explicit instantiation
    template void
    add_bias<float>(float *data_matrix, const float *bias, int rows, int columns);
}
