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

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/opencl.h>
#endif

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
     * Adds zero padding to a matrix so the x and y dimensions are multiples of padding.
     * The padding is applied to the left and the bottom.
     *
     * @param padding the matrix will be padded so x and y are a factor of padding
     * @param x size of x dimension
     * @param y size of y dimension
     * @param input float pointer holding the data
     * @param paddedX size of x the padded matrix
     * @param paddedY size of y of the padded matrix
     * @return float pointer holding the padded data, needs to be deallocated by the caller
     */
    float *add_padding(int padding, int x, int y, const float *input, int *paddedX, int *paddedY);

    /**
     * Removes zero padding that was applied to a matrix
     *
     * @param padding padding that was applied
     * @param x desired size of x dimension
     * @param y desized size of y dimension
     * @param input float pointer holding the padded data
     * @return float pointer holding the unpadded data, needs to be deallocated by the caller
     */
    float *remove_padding(int padding, int x, int y, const float *input);

    /**
     * Transpose a matrix
     *
     * @param sizeX x dimension of the matrix
     * @param sizeY y dimension of the matrix
     * @param input pointer holding the data
     * @return float pointer with the transposed data, needs to deallocated by the caller
     */
    float *transpose(int sizeX, int sizeY, const float *input);

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

    /**
     * Returns the corresponding OpenCL error message for a given OpenCL error code.
     *
     * @param error                 The OpenCL error code of a OpenCL function.
     * @return                      Returns the corresponding OpenCL error message.
     */
    const char *getErrorString(cl_int error);

    /**
     * Takes the return code of a OpenCL function and checks whether the OpenCL function was successful.
     * If the OpenCL function was not succesful, an exception of kind @T with the message @message is thrown.
     *
     * @tparam T        The kind of exception that should be thrown in case a OpenCL function was not successful.
     * @param error     The OpenCL error code returned by a OpenCL function.
     * @param message   A user-defined descriptive error message that will be the exception message.
     */
    template<typename T>
    void checkError(cl_int error, const std::string &message);

    /**
     * Loads an OpenCL kernel source file.
     *
     * @param name
     * @return a string representing the OpenCL kernel sources
     */
    std::string loadKernel(const char *name);

    /**
     * Creates a OpenCL program from a source file.
     *
     * @param source
     * @param context
     * @return
     */
    cl_program createProgramFromSource(cl_context context, const std::string &source);

    /*
     * Create a OpenCL program from a binary file.
     * The program is created for all given devices associated with the context. The same
     * binary is used for all devices.
     */
    cl_program createProgramFromBinary(cl_context context, const char *binary_file_name, const cl_device_id *devices,
                                       unsigned num_devices);

    /*
     * Returns the path to the AOCX file to use for the given device.
     * This is special handling for examples for the Altera SDK for OpenCL.
     * It uses the device name to get the board name and then looks for a
     * corresponding AOCX file. Specifically, it gets the device name and
     * extracts the board name assuming the device name has the following format:
     * <board> : ...
     *
     * Then the AOCX file is <prefix>_<version>_<board>.aocx. If this
     * file does not exist, then the file name defaults to <prefix>.aocx.
     */
    std::string getBoardBinaryFile(const char *prefix, cl_device_id device);
}
