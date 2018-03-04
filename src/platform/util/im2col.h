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
    void im2col_simple_version_cpu(const Dtype *data_image, int channels, int height, int width,
                                   int kernel_size, int padding, int stride,
                                   Dtype *data_column);

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
    void col2im_simple_version_cpu(const Dtype *data_column, int channels, int height, int width,
                                   int kernel_size, int padding, int stride,
                                   Dtype *data_image);

    template<typename Dtype>
    void add_bias(Dtype *data_matrix, const Dtype *bias, int number_of_rows, int number_of_columns);
}
