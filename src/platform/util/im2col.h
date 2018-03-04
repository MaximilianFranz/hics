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

#pragma once

namespace helper {

    /**
     * Multiplies two matrices that are both given as one-dimensional vector.
     *
     * @param matrix_left               The left matrix of the matrix multiplication.
     * @param matrix_left_rows          The number of rows of the left matrix.
     * @param matrix_left_columns       The number of columns of the left matrix.
     * @param matrix_right              The right matrix of the matrix multiplication.
     * @param matrix_right_rows         The number of rows of the right matrix.
     * @param matrix_right_columns      The number of columns of the right matrix.
     * @param result_matrix             The result of the matrix multiplication.
     */
    void multiply_matrices_using_1d_vectors(const float *matrix_left, int matrix_left_rows, int matrix_left_columns,
                                            const float *matrix_right, int matrix_right_rows, int matrix_right_columns,
                                            float *result_matrix);

    /**
     * Performs the im2col algorithm on the CPU.
     *
     * @tparam Dtype                A data type representing a matrix.
     * @param data_image            The matrix that shall be reconstructed.
     * @param channels              The number of channels of the image matrix.
     * @param height                The height of the image matrix.
     * @param width                 The width of the image matrix.
     * @param kernel_size           The size of the quadratic kernel the image matrix shall be convolved with.
     * @param padding               The amount of padding that is used for the convolution.
     * @param stride                The stride of the kernel.
     * @param data_column           The reconstructed result matrix.
     */
    template<typename Dtype>
    void im2col_cpu(const Dtype *data_image, int channels, int height, int width, int kernel_size, int padding,
                    int stride, Dtype *data_column);

    /**
     * Performs the col2im algorithm on the CPU.
     *
     * @tparam Dtype                A data type representing a matrix.
     * @param data_column           The matrix that shall be reordered.
     * @param channels              The number of channels of the image matrix.
     * @param height                The height of the image matrix.
     * @param width                 The width of the image matrix.
     * @param kernel_size           The size of the quadratic kernel the image matrix shall be convolved with.
     * @param padding               The amount of padding that is used for the convolution.
     * @param stride                The stride of the kernel.
     * @param data_image            The reordered result matrix.
     */
    template<typename Dtype>
    void col2im_cpu(const Dtype *data_column, int channels, int height, int width, int kernel_size, int padding,
                    int stride, Dtype *data_image);

    /**
     * Adds a bias to the values of a matrix.
     *
     * @tparam Dtype                A data type representing a matrix.
     * @param data_matrix           The matrix to whose values a bias shall be added.
     * @param bias                  The matrix containing the bias values.
     * @param number_of_rows        The number of rows both matrices have.
     * @param number_of_columns     The number of columns both matrices have.
     */
    template<typename Dtype>
    void add_bias(Dtype *data_matrix, const Dtype *bias, int number_of_rows, int number_of_columns);

}
