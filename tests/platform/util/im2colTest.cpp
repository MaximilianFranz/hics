#include "im2colTest.h"

#include <iostream>
#include <util/im2col.h>
#include <fstream>
#include <iterator>

TEST_CASE("Matrix multiplication using 1d vectors") {

    SECTION("A") {
        int matrix_left_rows, matrix_left_columns, matrix_right_rows, matrix_right_columns;
        matrix_left_rows = 3;
        matrix_left_columns = matrix_right_rows = 3;
        matrix_right_columns = 3;

        auto matrix_left = std::vector<float>{11, 12, 15, 16, 17, 18, 95, 96, 97};
        auto matrix_right = std::vector<float>{39, 27, 82, 14, 63, 6, 32, 78, 44};

        REQUIRE((matrix_left_rows * matrix_left_columns) == matrix_left.size());
        REQUIRE((matrix_right_rows * matrix_right_columns) == matrix_right.size());
        REQUIRE(matrix_left_columns == matrix_right_rows);

        auto elements_in_result_matrix = matrix_left_rows * matrix_right_columns;
        auto multiplication_result = std::vector<float>(static_cast<unsigned long>(elements_in_result_matrix));

        helper::multiply_matrices_using_1d_vectors(matrix_left.data(), matrix_left_rows, matrix_left_columns,
                                                   matrix_right.data(), matrix_right_rows, matrix_right_columns,
                                                   multiplication_result.data());


        auto expected_result = std::vector<float>{1077, 2223, 1634, 1438, 2907, 2206, 8153, 16179, 12634};

        REQUIRE(elements_in_result_matrix == expected_result.size());

        REQUIRE(std::equal(expected_result.begin(), expected_result.end(), multiplication_result.begin()));
    }

    SECTION("B") {
        int matrix_left_rows, matrix_left_columns, matrix_right_rows, matrix_right_columns;
        matrix_left_rows = 2;
        matrix_left_columns = matrix_right_rows = 5;
        matrix_right_columns = 3;

        auto matrix_left = std::vector<float>{11, 12, 15, 16, 17, 18, 95, 96, 97, 98};
        auto matrix_right = std::vector<float>{39, 27, 82, 14, 63, 6, 32, 78, 44, 53, 75, 23, 53, 18, 72};

        REQUIRE((matrix_left_rows * matrix_left_columns) == matrix_left.size());
        REQUIRE((matrix_right_rows * matrix_right_columns) == matrix_right.size());
        REQUIRE(matrix_left_columns == matrix_right_rows);

        auto elements_in_result_matrix = matrix_left_rows * matrix_right_columns;
        auto multiplication_result = std::vector<float>(static_cast<unsigned long>(elements_in_result_matrix));

        helper::multiply_matrices_using_1d_vectors(matrix_left.data(), matrix_left_rows, matrix_left_columns,
                                                   matrix_right.data(), matrix_right_rows, matrix_right_columns,
                                                   multiplication_result.data());


        auto expected_result = std::vector<float>{2826, 3729, 3226, 15439, 22998, 15557};

        REQUIRE(elements_in_result_matrix == expected_result.size());

        REQUIRE(std::equal(expected_result.begin(), expected_result.end(), multiplication_result.begin()));
    }

    SECTION("C") {
        int matrix_left_rows, matrix_left_columns, matrix_right_rows, matrix_right_columns;
        matrix_left_rows = 1;
        matrix_left_columns = matrix_right_rows = 4;
        matrix_right_columns = 4;

        auto matrix_left = std::vector<float>{1, 2, 3, 4};
        auto matrix_right = std::vector<float>{1, 2, 4, 5, 2, 3, 5, 6, 4, 5, 7, 8, 5, 6, 8, 9};

        REQUIRE((matrix_left_rows * matrix_left_columns) == matrix_left.size());
        REQUIRE((matrix_right_rows * matrix_right_columns) == matrix_right.size());
        REQUIRE(matrix_left_columns == matrix_right_rows);

        auto elements_in_result_matrix = matrix_left_rows * matrix_right_columns;
        auto multiplication_result = std::vector<float>(static_cast<unsigned long>(elements_in_result_matrix));

        helper::multiply_matrices_using_1d_vectors(matrix_left.data(), matrix_left_rows, matrix_left_columns,
                                                   matrix_right.data(), matrix_right_rows, matrix_right_columns,
                                                   multiplication_result.data());

        auto expected_result = std::vector<float>{37, 47, 67, 77};

        REQUIRE(elements_in_result_matrix == expected_result.size());

        REQUIRE(std::equal(expected_result.begin(), expected_result.end(), multiplication_result.begin()));
    }
}

TEST_CASE("col2im for 3x3x1 images with 1 kernel") {
    int image_size = 3;
    int channels = 1;

    int kernel_size = 2;
    int number_of_kernels = 1;

    int padding = 0;
    int stride = 1;

    int output_size = (image_size - kernel_size + 2 * padding) / stride + 1;

    int multiplication_result_rows, multiplication_result_columns, convolution_result_size;
    multiplication_result_columns = output_size * output_size;
    multiplication_result_rows = number_of_kernels;
    convolution_result_size = output_size * output_size * number_of_kernels;

    SECTION("A") {
        /*
         * Wolfram Alpha query:
         * {1,2,3,4}.{{1,2,4,5},{2,3,5,6},{4,5,7,8},{5,6,8,9}}
         */
        auto multiplication_result = std::vector<float>{37, 47, 67, 77};

        auto convolution_result = std::vector<float>(static_cast<unsigned long>(convolution_result_size));

        helper::col2im_simple_version_cpu(multiplication_result.data(),
                                          channels, multiplication_result_rows, multiplication_result_columns,
                                          kernel_size,
                                          padding, stride,
                                          convolution_result.data());

        auto expected_convolution_result = std::vector<float>{37, 47, 67, 77};

        REQUIRE(convolution_result.size() == convolution_result_size);
        REQUIRE(expected_convolution_result.size() == convolution_result_size);
        REQUIRE(expected_convolution_result == convolution_result);
    }

    SECTION("B") {
        /*
         * Wolfram Alpha query:
         * {1,2,3,4}.{{1,2,4,5},{2,3,5,6},{4,5,7,8},{5,6,8,9}}
         */
        auto multiplication_result = std::vector<float>{37, 47, 67, 77};

        auto convolution_result = std::vector<float>(static_cast<unsigned long>(convolution_result_size));

        helper::col2im_simple_version_cpu(multiplication_result.data(),
                                          channels, multiplication_result_rows, multiplication_result_columns,
                                          kernel_size,
                                          padding, stride,
                                          convolution_result.data());

        auto expected_convolution_result = std::vector<float>{37, 47, 67, 77};

        REQUIRE(convolution_result.size() == convolution_result_size);
        REQUIRE(expected_convolution_result.size() == convolution_result_size);
        REQUIRE(expected_convolution_result == convolution_result);
    }
}

TEST_CASE("col2im for 3x3x2 images with 1 kernel") {
    int image_size = 3;
    int channels = 2;

    int kernel_size = 2;
    int number_of_kernels = 1;

    int padding = 0;
    int stride = 1;

    int output_size = (image_size - kernel_size + 2 * padding) / stride + 1;

    int multiplication_result_rows, multiplication_result_columns, convolution_result_size;
    multiplication_result_columns = output_size * output_size;
    multiplication_result_rows = number_of_kernels;
    convolution_result_size = output_size * output_size * number_of_kernels;

    SECTION("A") {
        /*
         * Wolfram Alpha query:
         * {1,2,3,4,5,6,7,8}.{{1,2,4,5},{2,3,5,6},{4,5,7,8},{5,6,8,9},{10,11,13,14},{11,12,14,15},{13,14,16,17},{14,15,17,18}}
         */
        auto multiplication_result = std::vector<float>{356, 392, 464, 500};

        auto convolution_result = std::vector<float>(static_cast<unsigned long>(convolution_result_size));

        helper::col2im_simple_version_cpu(multiplication_result.data(),
                                          channels, multiplication_result_rows, multiplication_result_columns,
                                          kernel_size,
                                          padding, stride,
                                          convolution_result.data());

        auto expected_convolution_result = std::vector<float>{356, 392, 464, 500};

        REQUIRE(convolution_result.size() == convolution_result_size);
        REQUIRE(expected_convolution_result.size() == convolution_result_size);
        REQUIRE(expected_convolution_result == convolution_result);
    }
}

//TEST_CASE("col2im for 3x3x2 images with 3 kernels") {
//    int image_size = 3;
//    int channels = 2;
//
//    int kernel_size = 2;
//    int number_of_kernels = 3;
//
//    int padding = 0;
//    int stride = 1;
//
//    int output_size = (image_size - kernel_size + 2 * padding) / stride + 1;
//
//    int multiplication_result_rows, multiplication_result_columns, convolution_result_size;
//    multiplication_result_columns = output_size * output_size;
//    multiplication_result_rows = number_of_kernels;
//    convolution_result_size = output_size * output_size * number_of_kernels;
//
//    SECTION("A") {
//        /*
//         * Wolfram Alpha query:
//         * {{1,2,3,4,5,6,7,8},{9,10,11,12,13,14,15,16},{17,18,19,20,21,22,23,24}}.{{1,2,4,5},{2,3,5,6},{4,5,7,8},{5,6,8,9},{10,11,13,14},{11,12,14,15},{13,14,16,17},{14,15,17,18}}
//         */
//        auto multiplication_result = std::vector<float>{356, 392, 464, 500, 836, 936, 1136, 1236, 1316, 1480, 1808,
//                                                        1972};
//
//        auto convolution_result = std::vector<float>(static_cast<unsigned long>(convolution_result_size));
//
//        helper::col2im_simple_version_cpu(multiplication_result.data(),
//                                          channels, multiplication_result_rows, multiplication_result_columns,
//                                          kernel_size,
//                                          padding, stride,
//                                          convolution_result.data());
//
//        auto expected_convolution_result = std::vector<float>{356, 392, 464, 500, 836, 936, 1136, 1236, 1316, 1480,
//                                                              1808, 1972};
//
//        REQUIRE(convolution_result.size() == convolution_result_size);
//        REQUIRE(expected_convolution_result.size() == convolution_result_size);
//        REQUIRE(expected_convolution_result == convolution_result);
//    }
//}

TEST_CASE("3x3x1 image and 3x3x1 kernel") {
    int image_size = 3;
    int kernel_size = 3;
    int channels = 1;
    int padding = 0;
    int stride = 1;
    int output_size = (image_size - kernel_size + 2 * padding) / stride + 1;

    auto elements_in_im2col_matrix = kernel_size * kernel_size * channels * output_size * output_size;
    auto column = std::vector<float>(static_cast<unsigned long>(elements_in_im2col_matrix));
    auto column_back_to_image = std::vector<float>(static_cast<unsigned long>(elements_in_im2col_matrix));

    SECTION("A") {
        auto image = std::vector<float>{1, 2, 3, 4, 5, 6, 7, 8, 9};

        helper::im2col_simple_version_cpu(image.data(), channels, image_size, image_size, kernel_size, padding,
                                          stride,
                                          column.data());

        auto expected_im2col_result = std::vector<float>{1, 2, 3, 4, 5, 6, 7, 8, 9};

        REQUIRE(elements_in_im2col_matrix == column.size());
        REQUIRE(elements_in_im2col_matrix == expected_im2col_result.size());
        REQUIRE(column == expected_im2col_result);
        REQUIRE(std::equal(column.begin(), column.end(), expected_im2col_result.begin()));
    }

    SECTION("B") {
        auto image = std::vector<float>{1, 4, 7, 2, 5, 8, 3, 6, 9};

        helper::im2col_simple_version_cpu(image.data(), channels, image_size, image_size, kernel_size, padding,
                                          stride,
                                          column.data());

        auto expected_im2col_result = std::vector<float>{1, 4, 7, 2, 5, 8, 3, 6, 9};

        REQUIRE(elements_in_im2col_matrix == column.size());
        REQUIRE(elements_in_im2col_matrix == expected_im2col_result.size());
        REQUIRE(column == expected_im2col_result);
        REQUIRE(std::equal(column.begin(), column.end(), expected_im2col_result.begin()));

        helper::col2im_simple_version_cpu(expected_im2col_result.data(), channels, image_size, image_size, kernel_size,
                                          padding,
                                          stride, column.data());
    }
}

TEST_CASE("3x3x1 image and 2x2x1 kernel") {
    int image_size = 3;
    int kernel_size = 2;
    int channels = 1;
    int padding = 0;
    int stride = 1;
    int number_of_kernels = 1;

    int im2col_matrix_rows, im2col_matrix_columns,
            weight_matrix_rows, weight_matrix_columns,
            multiplication_result_rows, multiplication_result_columns,
            convolved_image_size;

    int output_size = (image_size - kernel_size + 2 * padding) / stride + 1;

    im2col_matrix_rows = weight_matrix_columns = multiplication_result_rows = kernel_size * kernel_size * channels;
    im2col_matrix_columns = multiplication_result_columns = output_size * output_size;
    weight_matrix_rows = multiplication_result_rows = number_of_kernels;

    auto elements_in_im2col_matrix = kernel_size * kernel_size * channels * output_size * output_size;
    auto column = std::vector<float>(static_cast<unsigned long>(elements_in_im2col_matrix));

    SECTION("A") {
        auto image = std::vector<float>{1, 4, 7, 2, 5, 8, 3, 6, 9};

        helper::im2col_simple_version_cpu(image.data(), channels, image_size, image_size, kernel_size, padding,
                                          stride,
                                          column.data());

        auto expected_im2col_result = std::vector<float>{1, 4, 2, 5, 4, 7, 5, 8, 2, 5, 3, 6, 5, 8, 6, 9};

        REQUIRE(elements_in_im2col_matrix == column.size());
        REQUIRE(elements_in_im2col_matrix == expected_im2col_result.size());
        REQUIRE(column == expected_im2col_result);
        REQUIRE(std::equal(column.begin(), column.end(), expected_im2col_result.begin()));
    }

    SECTION("B") {
        auto image = std::vector<float>{1, 2, 3, 4, 5, 6, 7, 8, 9};

        helper::im2col_simple_version_cpu(image.data(), channels, image_size, image_size, kernel_size, padding,
                                          stride,
                                          column.data());

        auto expected_im2col_result = std::vector<float>{1, 2, 4, 5, 2, 3, 5, 6, 4, 5, 7, 8, 5, 6, 8, 9};

        REQUIRE(elements_in_im2col_matrix == column.size());
        REQUIRE(elements_in_im2col_matrix == expected_im2col_result.size());
        REQUIRE(column == expected_im2col_result);
        REQUIRE(std::equal(column.begin(), column.end(), expected_im2col_result.begin()));

        // TODO matrix multiplication
        auto weight_matrix = std::vector<float>{1, 2, 3, 4};
        auto multiplication_result = std::vector<float>(
                static_cast<unsigned long>(multiplication_result_rows * multiplication_result_columns));

        helper::multiply_matrices_using_1d_vectors(weight_matrix.data(), weight_matrix_rows, weight_matrix_columns,
                                                   column.data(), im2col_matrix_rows, im2col_matrix_columns,
                                                   multiplication_result.data());

        auto expected_result = std::vector<float>{37, 47, 67, 77};

        auto elements_in_result_matrix = multiplication_result_rows * multiplication_result_columns;
        REQUIRE(elements_in_result_matrix == expected_result.size());

        REQUIRE(std::equal(expected_result.begin(), expected_result.end(), multiplication_result.begin()));


        // TODO col2im
    }
}

TEST_CASE("3x3x2 image and 2x2x2 kernel") {
    int image_size = 3;
    int kernel_size = 2;
    int channels = 2;
    int padding = 0;
    int stride = 1;
    int number_of_kernels = 1;

    int im2col_matrix_rows, im2col_matrix_columns,
            weight_matrix_rows, weight_matrix_columns,
            multiplication_result_rows, multiplication_result_columns,
            convolved_image_size;

    int output_size = (image_size - kernel_size + 2 * padding) / stride + 1;

    im2col_matrix_rows = weight_matrix_columns = multiplication_result_rows = kernel_size * kernel_size * channels;
    im2col_matrix_columns = multiplication_result_columns = output_size * output_size;
    weight_matrix_rows = multiplication_result_rows = number_of_kernels;

    auto elements_in_im2col_matrix = kernel_size * kernel_size * channels * output_size * output_size;
    auto column = std::vector<float>(static_cast<unsigned long>(elements_in_im2col_matrix));

    SECTION("A") {
        auto image = std::vector<float>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};

        helper::im2col_simple_version_cpu(image.data(), channels, image_size, image_size, kernel_size, padding,
                                          stride,
                                          column.data());

        auto expected_im2col_result = std::vector<float>{1, 2, 4, 5, 2, 3, 5, 6, 4, 5, 7, 8, 5, 6, 8, 9, 10, 11, 13, 14,
                                                         11, 12, 14, 15, 13, 14, 16, 17, 14, 15, 17, 18};

        REQUIRE(elements_in_im2col_matrix == column.size());
        REQUIRE(elements_in_im2col_matrix == expected_im2col_result.size());
        REQUIRE(column == expected_im2col_result);
        REQUIRE(std::equal(column.begin(), column.end(), expected_im2col_result.begin()));

        auto weight_matrix = std::vector<float>{1, 2, 3, 4, 5, 6, 7, 8};
        auto multiplication_result = std::vector<float>(
                static_cast<unsigned long>(multiplication_result_rows * multiplication_result_columns));

        helper::multiply_matrices_using_1d_vectors(weight_matrix.data(), weight_matrix_rows, weight_matrix_columns,
                                                   column.data(), im2col_matrix_rows, im2col_matrix_columns,
                                                   multiplication_result.data());

        auto expected_result = std::vector<float>{356, 392, 464, 500};

        auto elements_in_result_matrix = multiplication_result_rows * multiplication_result_columns;
        REQUIRE(elements_in_result_matrix == expected_result.size());

        REQUIRE(std::equal(expected_result.begin(), expected_result.end(), multiplication_result.begin()));

    }
}

TEST_CASE("4x4x1 image and 2x2x1 kernel") {
    int image_size = 4;
    int kernel_size = 2;
    int channels = 1;
    int padding = 0;
    int stride = 1;
    int output_size = (image_size - kernel_size + 2 * padding) / stride + 1;

    auto elements_in_im2col_matrix = kernel_size * kernel_size * channels * output_size * output_size;
    auto column = std::vector<float>(static_cast<unsigned long>(elements_in_im2col_matrix));

    SECTION("A") {
        auto image = std::vector<float>{1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16};

        helper::im2col_simple_version_cpu(image.data(), channels, image_size, image_size, kernel_size, padding,
                                          stride,
                                          column.data());

        auto expected_im2col_result = std::vector<float>{1, 5, 9, 2, 6, 10, 3, 7, 11, 5, 9, 13, 6, 10, 14, 7, 11, 15, 2,
                                                         6, 10, 3, 7, 11, 4, 8, 12, 6, 10, 14, 7, 11, 15, 8, 12, 16};

        REQUIRE(elements_in_im2col_matrix == column.size());
        REQUIRE(elements_in_im2col_matrix == expected_im2col_result.size());
        REQUIRE(column == expected_im2col_result);
        REQUIRE(std::equal(column.begin(), column.end(), expected_im2col_result.begin()));
    }

    SECTION("B") {
        auto image = std::vector<float>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

        helper::im2col_simple_version_cpu(image.data(), channels, image_size, image_size, kernel_size, padding,
                                          stride,
                                          column.data());

        auto expected_im2col_result = std::vector<float>{1, 2, 3, 5, 6, 7, 9, 10, 11, 2, 3, 4, 6, 7, 8, 10, 11, 12, 5,
                                                         6, 7, 9, 10, 11, 13, 14, 15, 6, 7, 8, 10, 11, 12, 14, 15, 16};

        REQUIRE(elements_in_im2col_matrix == column.size());
        REQUIRE(elements_in_im2col_matrix == expected_im2col_result.size());
        REQUIRE(column == expected_im2col_result);
        REQUIRE(std::equal(column.begin(), column.end(), expected_im2col_result.begin()));
    }

}

TEST_CASE("4x4x1 image and 3x3x1 kernel") {
    int image_size = 4;
    int kernel_size = 3;
    int channels = 1;
    int padding = 0;
    int stride = 1;
    int output_size = (image_size - kernel_size + 2 * padding) / stride + 1;

    auto elements_in_im2col_matrix = kernel_size * kernel_size * channels * output_size * output_size;
    auto column = std::vector<float>(static_cast<unsigned long>(elements_in_im2col_matrix));

    SECTION("A") {
        auto image = std::vector<float>{1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16};

        helper::im2col_simple_version_cpu(image.data(), channels, image_size, image_size, kernel_size, padding,
                                          stride,
                                          column.data());

        auto expected_im2col_result = std::vector<float>{1, 5, 2, 6, 5, 9, 6, 10, 9, 13, 10, 14, 2, 6, 3, 7, 6, 10, 7,
                                                         11, 10, 14, 11, 15, 3, 7, 4, 8, 7, 11, 8, 12, 11, 15, 12, 16};

        REQUIRE(elements_in_im2col_matrix == column.size());
        REQUIRE(elements_in_im2col_matrix == expected_im2col_result.size());
        REQUIRE(column == expected_im2col_result);
        REQUIRE(std::equal(column.begin(), column.end(), expected_im2col_result.begin()));
    }

    SECTION("B") {
        auto image = std::vector<float>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

        helper::im2col_simple_version_cpu(image.data(), channels, image_size, image_size, kernel_size, padding,
                                          stride,
                                          column.data());

        auto expected_im2col_result = std::vector<float>{1, 2, 5, 6, 2, 3, 6, 7, 3, 4, 7, 8, 5, 6, 9, 10, 6, 7, 10, 11,
                                                         7, 8, 11, 12, 9, 10, 13, 14, 10, 11, 14, 15, 11, 12, 15, 16};

        REQUIRE(elements_in_im2col_matrix == column.size());
        REQUIRE(elements_in_im2col_matrix == expected_im2col_result.size());
        REQUIRE(column == expected_im2col_result);
        REQUIRE(std::equal(column.begin(), column.end(), expected_im2col_result.begin()));
    }
}
//
//TEST_CASE("Entire run with 3x3x1 image and one 2x2x1 kernel") {
//    int image_size = 3;
//    int channels = 1;
//
//    int kernel_size = 2;
//    int number_of_kernels = 1;
//
//    int padding = 0;
//    int stride = 1;
//
//    int output_size = (image_size - kernel_size + 2 * padding) / stride + 1;
//
//    int im2col_matrix_rows, im2col_matrix_columns, weight_matrix_rows, weight_matrix_columns, multiplication_result_rows, multiplication_result_columns, convolution_result_size;
//    im2col_matrix_rows = weight_matrix_columns = multiplication_result_rows = kernel_size * kernel_size * channels;
//    im2col_matrix_columns = multiplication_result_columns = output_size * output_size;
//    weight_matrix_rows = multiplication_result_rows = number_of_kernels;
//    auto weight_matrix_size = weight_matrix_rows * weight_matrix_columns;
//    convolution_result_size = output_size * output_size * number_of_kernels;
//
//
//    auto column_matrix_size = im2col_matrix_rows * im2col_matrix_columns;
//    auto column = std::vector<float>(static_cast<unsigned long>(column_matrix_size));
//
//    SECTION("A") {
//        auto image = std::vector<float>{1, 2, 3, 4, 5, 6, 7, 8, 9};
//        auto weight_matrix = std::vector<float>{1, 2, 3, 4};
//
//        helper::im2col_simple_version_cpu(image.data(), channels, image_size, image_size, kernel_size, padding,
//                                          stride,
//                                          column.data());
//
//        auto expected_column_matrix = std::vector<float>{1, 2, 4, 5, 2, 3, 5, 6, 4, 5, 7, 8, 5, 6, 8, 9};
//
//
//        REQUIRE(column.size() == column_matrix_size);
//        REQUIRE(expected_column_matrix.size() == column_matrix_size);
//        REQUIRE(column == expected_column_matrix);
//
//        auto multiplication_result_size = multiplication_result_rows * multiplication_result_columns;
//        auto multiplication_result = std::vector<float>(static_cast<unsigned long>(multiplication_result_size));
//
//        helper::multiply_matrices_using_1d_vectors(weight_matrix.data(), weight_matrix_rows, weight_matrix_columns,
//                                                   column.data(), im2col_matrix_rows, im2col_matrix_columns,
//                                                   multiplication_result.data());
//
//        /*
//         * Wolfram Alpha query:
//         * {1,2,3,4}.{{1,2,4,5},{2,3,5,6},{4,5,7,8},{5,6,8,9}}
//         */
//        auto expected_multiplication_result = std::vector<float>{37, 47, 67, 77};
//
//        REQUIRE(multiplication_result_size == multiplication_result.size());
//        REQUIRE(expected_multiplication_result.size() == convolution_result_size);
//        REQUIRE(multiplication_result == expected_multiplication_result);
//
//        auto convolution_result = std::vector<float>(static_cast<unsigned long>(convolution_result_size));
//
//        helper::col2im_simple_version_cpu(multiplication_result.data(),
//                                          channels, multiplication_result_rows, multiplication_result_columns,
//                                          kernel_size,
//                                          padding, stride,
//                                          convolution_result.data());
//
//        auto expected_convolution_result = std::vector<float>{37, 47, 67, 77};
//
//        REQUIRE(convolution_result.size() == convolution_result_size);
//        REQUIRE(expected_convolution_result.size() == convolution_result_size);
//        REQUIRE(expected_convolution_result == convolution_result);
//    }
//}

template<typename T>
std::vector<T> split_im2col(const std::string& line) {
    std::istringstream is(line);
    return std::vector<T>(std::istream_iterator<T>(is), std::istream_iterator<T>());
}

std::vector<float> getDataFromFile_im2col(std::string path) {
    char* resolved_path;
    // Getting the real path from execution dir.
    // We pass NULL and let realpath allocate the string which means we have to free() it later.
    resolved_path = realpath(path.c_str(), NULL);
    // Open file
    std::ifstream file(resolved_path);
    std::string str;

    file.seekg(0, std::ios::end);
    str.reserve(static_cast<unsigned long>(file.tellg()));
    file.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(file)),
               std::istreambuf_iterator<char>());

    std::vector<float> data = split_im2col<float>(str);

    free(resolved_path);
    return data;
}

TEST_CASE("Testing im2Col with real data") {
    std::string conv1_weights_path = "../../../tests/resources/conv1_weight.txt";
    std::string conv1_result_path = "../../../tests/resources/conv1_data_alexnet.txt";
    std::string img_data_path = "../../../tests/resources/img_data.txt";
    std::string conv1_bias_path = "../../../tests/resources/conv1_bias.txt";

    std::vector<float> weights = getDataFromFile_im2col(conv1_weights_path);
    std::vector<float> bias = getDataFromFile_im2col(conv1_bias_path);
    std::vector<float> img = getDataFromFile_im2col(img_data_path);
    std::vector<float> result_excpected = getDataFromFile_im2col(conv1_result_path);

    std::vector<float> patch_result(363*3025);

    std::vector<float> matmul_result(55*55*96);

    helper::im2col_simple_version_cpu(img.data(), 3, 227, 227, 11, 0,
                                      4,
                                      patch_result.data());

    helper::multiply_matrices_using_1d_vectors(weights.data(), 96, 363,
                                               patch_result.data(), 363, 3025,
                                               matmul_result.data());

    helper::add_bias(matmul_result.data(), bias.data(), 96, 55, 96);

    for (int i = 0; i < 6025; i++) {
        REQUIRE(std::abs(matmul_result.at(i) - result_excpected.at(i)) < 0.01);
    }

}
