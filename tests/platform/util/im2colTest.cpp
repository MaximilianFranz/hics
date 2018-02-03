#include "im2colTest.h"

#include <iostream>
#include <util/im2col.h>

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

TEST_CASE("col2im") {

}

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
