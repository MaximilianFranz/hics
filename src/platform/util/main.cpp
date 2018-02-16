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

#include <vector>
#include <iostream>
#include <wrapper/ImageWrapper.h>
#include <util/im2col.h>
#include <cassert>

int main(int argc, char *argv[]) {
    int image_size = 3;
    int channels = 2;
    channels = 1;

    int kernel_size = 2;
    int number_of_kernels = 3;
    number_of_kernels = 1;

    int padding = 0;
    int stride = 1;

    int output_size = (image_size - kernel_size + 2 * padding) / stride + 1;

    std::cout << "Image size: " << image_size << "x" << image_size << "x" << channels << std::endl;
    std::cout << "Kernel size: " << kernel_size << "x" << kernel_size << "x" << channels << std::endl;
    std::cout << "Padding: " << padding << std::endl;
    std::cout << "Stride: " << stride << std::endl;
    std::cout << std::endl;

    std::cout << "=================================" << std::endl;
    std::cout << std::endl;

    int im2col_matrix_rows, im2col_matrix_columns, weight_matrix_rows, weight_matrix_columns, multiplication_result_rows, multiplication_result_columns, convolution_result_size;
    im2col_matrix_rows = weight_matrix_columns = multiplication_result_rows = kernel_size * kernel_size * channels;
    im2col_matrix_columns = multiplication_result_columns = output_size * output_size;

    auto image = std::vector<float>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};
    image = std::vector<float>{1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::cout << "Input Image: " << std::endl;
    std::cout << "Anzahl der Channels: " << channels << std::endl;
    std::cout << "Erwartete Anzahl der Zeilen: " << image_size * channels << " (pro channel " << image_size
              << " Zeilen, dann der nächste Channel)" << std::endl;
    std::cout << "Erwartete Anzahl der Spalten: " << image_size << std::endl;
    std::cout << std::endl;

    int counter = 0;
    for (std::vector<float>::const_iterator i = image.begin(); i != image.end(); ++i) {
        if (counter >= image_size) {
            std::cout << std::endl;
            counter = 0;
        }
        std::cout << *i << ' ';
        counter++;
    }

    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "=================================" << std::endl;
    std::cout << std::endl;

    std::cout << "Output Matrix M of im2col:" << std::endl;
    std::cout << "Erwartete Anzahl der Zeilen: " << im2col_matrix_rows << " (" << kernel_size * kernel_size
              << " Zeilen pro Channel)" << std::endl;
    std::cout << "Erwartete Anzahl der Spalten: " << im2col_matrix_columns << std::endl;
    std::cout << std::endl;

    auto column_matrix_size = im2col_matrix_rows * im2col_matrix_columns;
    auto column = std::vector<float>(static_cast<unsigned long>(column_matrix_size));

    helper::im2col_simple_version_cpu(image.data(), channels, image_size, image_size, kernel_size, padding, stride,
                                      column.data());

    assert(column.size() == static_cast<unsigned long>(column_matrix_size));

    counter = 0;
    for (std::vector<float>::const_iterator i = column.begin(); i != column.end(); ++i) {

        if (counter >= im2col_matrix_columns) {
            std::cout << std::endl;
            counter = 0;
        }

        std::cout << *i << ' ';
        counter++;
    }

    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "=================================" << std::endl;
    std::cout << std::endl;

    weight_matrix_rows = multiplication_result_rows = number_of_kernels;

    std::cout << "Weight Matrix W:" << std::endl;
    std::cout << "Erwartete Anzahl der Zeilen: " << weight_matrix_rows
              << " (jede Zeile entspricht einem zu einer Zeile transformierten Kernel)" << std::endl;
    std::cout << "Erwartete Anzahl der Spalten: " << weight_matrix_columns
              << " (entspricht kernel_size*kernel_size*channels, also "
              << kernel_size << "*" << kernel_size << "*" << channels << ")" << std::endl;
    std::cout << std::endl;

    auto weight_matrix_size = weight_matrix_rows * weight_matrix_columns;
    auto weight_matrix = std::vector<float>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
                                            22, 23, 24};
    weight_matrix = std::vector<float>{1, 2, 3, 4};

    // TODO weight matrix muss glaube ich erst mit 1x1 Kernel abgelaufen werden, damit sie als Spalte geschrieben wird
    // TODO und danach muss das Ergebnis noch transponiert werden, damit die Einträge als Zeile geschrieben werden

    auto expected_weight_matrix = std::vector<float>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
                                                     20, 21, 22, 23, 24};
    expected_weight_matrix = std::vector<float>{1, 2, 3, 4};

    assert(weight_matrix.size() == static_cast<unsigned long>(weight_matrix_size));
    assert(expected_weight_matrix.size() == static_cast<unsigned long>(weight_matrix_size));

    counter = 0;
    for (std::vector<float>::const_iterator i = weight_matrix.begin(); i != weight_matrix.end(); ++i) {

        if (counter >= weight_matrix_columns) {
            std::cout << std::endl;
            counter = 0;
        }

        std::cout << *i << ' ';
        counter++;
    }

    assert(std::equal(expected_weight_matrix.begin(), expected_weight_matrix.end(), weight_matrix.begin()));

    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "=================================" << std::endl;
    std::cout << std::endl;

    std::cout << "Multiplication Result W*M:" << std::endl;
    std::cout << "Erwartete Anzahl der Zeilen: " << multiplication_result_rows << std::endl;
    std::cout << "Erwartete Anzahl der Spalten: " << multiplication_result_columns << std::endl;
    std::cout << std::endl;

    auto multiplication_result_size = multiplication_result_rows * multiplication_result_columns;
    auto multiplication_result = std::vector<float>(static_cast<unsigned long>(multiplication_result_size));

    helper::multiply_matrices_using_1d_vectors(weight_matrix.data(), weight_matrix_rows, weight_matrix_columns,
                                               column.data(), im2col_matrix_rows, im2col_matrix_columns,
                                               multiplication_result.data());

    /*
     * Wolfram Alpha query:
     * {{1,2,3,4,5,6,7,8},{9,10,11,12,13,14,15,16},{17,18,19,20,21,22,23,24}}.{{1,2,4,5},{2,3,5,6},{4,5,7,8},{5,6,8,9},{10,11,13,14},{11,12,14,15},{13,14,16,17},{14,15,17,18}}
     * Multiplikation mit . dazwischen, nicht *
     */
    auto expected_multiplication_result = std::vector<float>{356, 392, 464, 500, 836, 936, 1136, 1236, 1316, 1480, 1808,
                                                             1972};
    /*
     * {1,2,3,4}.{{1,2,4,5},{2,3,5,6},{4,5,7,8},{5,6,8,9}}
     */
    expected_multiplication_result = std::vector<float>{37, 47, 67, 77};

    assert(multiplication_result.size() == static_cast<unsigned long>(multiplication_result_size));
    // TODO assert(expected_multiplication_result.size() == static_cast<unsigned long>(multiplication_result_size));

    counter = 0;
    for (std::vector<float>::const_iterator i = multiplication_result.begin(); i != multiplication_result.end(); ++i) {

        if (counter >= im2col_matrix_columns) {
            std::cout << std::endl;
            counter = 0;
        }

        std::cout << *i << ' ';
        counter++;
    }

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Expected Result:" << std::endl;
    counter = 0;
    for (std::vector<float>::const_iterator i = expected_multiplication_result.begin();
         i != expected_multiplication_result.end(); ++i) {

        if (counter >= im2col_matrix_columns) {
            std::cout << std::endl;
            counter = 0;
        }

        std::cout << *i << ' ';
        counter++;
    }

    // TODO assert(std::equal(expected_multiplication_result.begin(), expected_multiplication_result.end(),
    //multiplication_result.begin()));

    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "=================================" << std::endl;

    convolution_result_size = output_size * output_size * number_of_kernels;

    std::cout << std::endl;
    std::cout << "Rückrichtung mittels col2im um das finale Ergebnis der Convolution zu erhalten:" << std::endl;
    std::cout << std::endl;
    std::cout << "Anzahl der Channels: " << number_of_kernels << std::endl;
    std::cout << "Erwartete Anzahl der Zeilen: " << output_size * number_of_kernels << " (pro channel " << output_size
              << " Zeilen, dann der nächste Channel)" << std::endl;
    std::cout << "Erwartete Anzahl der Spalten: " << output_size << std::endl;
    std::cout << std::endl;

    auto convolution_result = std::vector<float>(static_cast<unsigned long>(convolution_result_size));

    helper::col2im_simple_version_cpu(multiplication_result.data(),
                                      channels, multiplication_result_rows, multiplication_result_columns,
                                      kernel_size,
                                      padding, stride,
                                      convolution_result.data());

    auto expected_convolution_result = std::vector<float>{37, 47, 67, 77}; // TODO

    assert(convolution_result.size() == static_cast<unsigned long>(convolution_result_size));
    assert(expected_convolution_result.size() == static_cast<unsigned long>(convolution_result_size));

    counter = 0;
    for (std::vector<float>::const_iterator i = convolution_result.begin(); i != convolution_result.end(); ++i) {
        if (counter >= output_size) {
            std::cout << std::endl;
            counter = 0;
        }

        std::cout << *i << ' ';
        counter++;
    }

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Expected Result:" << std::endl;
    for (std::vector<float>::const_iterator i = expected_convolution_result.begin();
         i != expected_convolution_result.end(); ++i) {

        if (counter >= output_size) {
            std::cout << std::endl;
            counter = 0;
        }

        std::cout << *i << ' ';
        counter++;
    }

    assert(std::equal(expected_convolution_result.begin(), expected_convolution_result.end(),
                      convolution_result.begin()));

    return 0;
}
