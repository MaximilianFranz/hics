#pragma once

namespace helper {

    /**
     * Multiplies two matrices that are both given as one-dimensional vector.
     *
     * @param matrix_left
     * @param matrix_left_rows
     * @param matrix_left_columns
     * @param matrix_right
     * @param matrix_right_rows
     * @param matrix_right_columns
     * @param result_matrix
     */
    void multiply_matrices_using_1d_vectors(const float *matrix_left, int matrix_left_rows, int matrix_left_columns,
                                            const float *matrix_right, int matrix_right_rows, int matrix_right_columns,
                                            float *result_matrix);

    /**
     * Performs the im2col algorithm on the CPU.
     *
     * @tparam Dtype
     * @param data_image
     * @param channels
     * @param height
     * @param width
     * @param kernel_size
     * @param padding
     * @param stride
     * @param data_column
     */
    template<typename Dtype>
    void im2col_cpu(const Dtype *data_image, int channels, int height, int width,
                    int kernel_size, int padding, int stride,
                    Dtype *data_column);

    template<typename Dtype>
    void im2col_simple_version_cpu(const Dtype *data_image, int channels, int height, int width,
                                   int kernel_size, int padding, int stride,
                                   Dtype *data_column);

    /**
     * Initializes data with a value. Necessary for the col2im algorithm.
     *
     * @tparam Dtype            a data type
     * @param object_size       the size of the data type, typically height * width * channels
     * @param fill_byte         this character (typicalls 0) gets copied into the object pointed to by destination.
     * @param object_to_fill    in the col2im algorithm, this would be the im (image).
     */
    template<typename Dtype>
    void set(int object_size, Dtype fill_byte, Dtype *object_to_fill);


    /**
     * Performs the col2im algorithm on the CPU.
     *
     * @tparam Dtype
     * @param data_column
     * @param channels
     * @param height
     * @param width
     * @param kernel_size
     * @param padding
     * @param stride
     * @param data_image
     */
    template<typename Dtype>
    void col2im_cpu(const Dtype *data_column, int channels, int height, int width,
                    int kernel_size, int padding, int stride,
                    Dtype *data_image);

    template<typename Dtype>
    void col2im_simple_version_cpu(const Dtype *data_column, int channels, int height, int width,
                                   int kernel_size, int padding, int stride,
                                   Dtype *data_image);

    template<typename Dtype>
    void add_bias(Dtype *data_matrix, const Dtype *bias, int number_of_rows, int number_of_columns);
}
