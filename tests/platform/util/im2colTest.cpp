#include "im2colTest.h"

#include <iostream>
#include <util/im2col.h>

/*
 * Verify results with Matlab:
 * https://de.mathworks.com/help/images/ref/im2col.html
 */

TEST_CASE("3x3x1 image and 3x3x1 kernel") {
    int image_size = 3;
    int kernel_size = 3;
    int channels = 1;
    int padding = 0;
    int stride = 1;
    int output_size = (image_size - kernel_size + 2 * padding) / stride + 1;

    auto column = std::vector<float>(
            static_cast<unsigned long>(kernel_size * kernel_size * channels * output_size * output_size));

    SECTION("") {
        auto image = std::vector<float>{1, 2, 3, 4, 5, 6, 7, 8, 9};

        helper::im2col_simple_version_cpu(image.data(), channels, image_size, image_size, kernel_size, padding, stride,
                                          column.data());

        // auto result = std::vector<float>{1, 4, 7, 2, 5, 8, 3, 6, 9};
        auto result = std::vector<float>{1, 2, 3, 4, 5, 6, 7, 8, 9};
        REQUIRE(column == result);
        REQUIRE(std::equal(column.begin(), column.end(), result.begin()));
    }

    SECTION("") {
        auto image = std::vector<float>{1, 4, 7, 2, 5, 8, 3, 6, 9};

        helper::im2col_simple_version_cpu(image.data(), channels, image_size, image_size, kernel_size, padding, stride,
                                          column.data());

        // auto result = std::vector<float>{1, 2, 3, 4, 5, 6, 7, 8, 9};
        auto result = std::vector<float>{1, 4, 7, 2, 5, 8, 3, 6, 9};
        REQUIRE(column == result);
        REQUIRE(std::equal(column.begin(), column.end(), result.begin()));
    }
}

TEST_CASE("3x3x1 image and 2x2x1 kernel") {
    int image_size = 3;
    int kernel_size = 2;
    int channels = 1;
    int padding = 0;
    int stride = 1;
    int output_size = (image_size - kernel_size + 2 * padding) / stride + 1;

    auto column = std::vector<float>(
            static_cast<unsigned long>(kernel_size * kernel_size * channels * output_size * output_size));

    SECTION("") {
        auto image = std::vector<float>{1, 4, 7, 2, 5, 8, 3, 6, 9};

        helper::im2col_simple_version_cpu(image.data(), channels, image_size, image_size, kernel_size, padding, stride,
                                          column.data());

        // auto result = std::vector<float>{1, 2, 4, 5, 2, 3, 5, 6, 4, 5, 7, 8, 5, 6, 8, 9};
        auto result = std::vector<float>{1, 4, 2, 5, 4, 7, 5, 8, 2, 5, 3, 6, 5, 8, 6, 9};
        REQUIRE(column == result);
        REQUIRE(std::equal(column.begin(), column.end(), result.begin()));
    }

    SECTION("") {
        auto image = std::vector<float>{1, 2, 3, 4, 5, 6, 7, 8, 9};

        helper::im2col_simple_version_cpu(image.data(), channels, image_size, image_size, kernel_size, padding, stride,
                                          column.data());

        // auto result = std::vector<float>{1, 4, 2, 5, 4, 7, 5, 8, 2, 5, 3, 6, 5, 8, 6, 9};
        auto result = std::vector<float>{1, 2, 4, 5, 2, 3, 5, 6, 4, 5, 7, 8, 5, 6, 8, 9};
        REQUIRE(column == result);
        REQUIRE(std::equal(column.begin(), column.end(), result.begin()));
    }
}

TEST_CASE("4x4x1 image and 2x2x1 kernel") {
    int image_size = 4;
    int kernel_size = 2;
    int channels = 1;
    int padding = 0;
    int stride = 1;
    int output_size = (image_size - kernel_size + 2 * padding) / stride + 1;

    auto column = std::vector<float>(
            static_cast<unsigned long>(kernel_size * kernel_size * channels * output_size * output_size));

    SECTION("") {
        auto image = std::vector<float>{1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16};

        helper::im2col_simple_version_cpu(image.data(), channels, image_size, image_size, kernel_size, padding, stride,
                                          column.data());

        /*
         * auto result = std::vector<float>{1, 2, 3, 5, 6, 7, 9, 10, 11, 2, 3, 4, 6, 7, 8, 10, 11, 12, 5, 6, 7, 9, 10,
         * 11, 13, 14, 15, 6, 7, 8, 10, 11, 12, 14, 15, 16};
         */
        auto result = std::vector<float>{1, 5, 9, 2, 6, 10, 3, 7, 11, 5, 9, 13, 6, 10, 14, 7, 11, 15, 2, 6, 10, 3, 7,
                                         11, 4, 8, 12, 6, 10, 14, 7, 11, 15, 8, 12, 16};
        REQUIRE(column == result);
        REQUIRE(std::equal(column.begin(), column.end(), result.begin()));
    }

    SECTION("") {
        auto image = std::vector<float>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

        helper::im2col_simple_version_cpu(image.data(), channels, image_size, image_size, kernel_size, padding, stride,
                                          column.data());

        // auto result = std::vector<float>{1, 5, 9, 2, 6, 10, 3, 7, 11, 5, 9, 13, 6, 10, 14, 7, 11, 15, 2, 6, 10,
        //                                             3, 7, 11, 4, 8, 12, 6, 10, 14, 7, 11, 15, 8, 12, 16};
        auto result = std::vector<float>{1, 2, 3, 5, 6, 7, 9, 10, 11, 2, 3, 4, 6, 7, 8, 10, 11, 12, 5, 6, 7, 9, 10, 11,
                                         13, 14, 15, 6, 7, 8, 10, 11, 12, 14, 15, 16};
        REQUIRE(column == result);
        REQUIRE(std::equal(column.begin(), column.end(), result.begin()));
    }

}

TEST_CASE("4x4x1 image and 3x3x1 kernel") {
    int image_size = 4;
    int kernel_size = 3;
    int channels = 1;
    int padding = 0;
    int stride = 1;
    int output_size = (image_size - kernel_size + 2 * padding) / stride + 1;

    auto column = std::vector<float>(
            static_cast<unsigned long>(kernel_size * kernel_size * channels * output_size * output_size));

    SECTION("") {
        auto image = std::vector<float>{1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16};

        helper::im2col_simple_version_cpu(image.data(), channels, image_size, image_size, kernel_size, padding, stride,
                                          column.data());

        /*
         * auto result = std::vector<float>{1, 2, 5, 6, 2, 3, 6, 7, 3, 4, 7, 8, 5, 6, 9, 10, 6, 7, 10, 11, 7, 8, 11,
         * 12, 9, 10, 13, 14, 10, 11, 14, 15, 11, 12, 15, 16};
         */
        auto result = std::vector<float>{1, 5, 2, 6, 5, 9, 6, 10, 9, 13, 10, 14, 2, 6, 3, 7, 6, 10, 7, 11, 10, 14, 11,
                                         15, 3, 7, 4, 8, 7, 11, 8, 12, 11, 15, 12, 16};
        REQUIRE(column == result);
        REQUIRE(std::equal(column.begin(), column.end(), result.begin()));
    }

    SECTION("") {
        auto image = std::vector<float>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

        helper::im2col_simple_version_cpu(image.data(), channels, image_size, image_size, kernel_size, padding, stride,
                                          column.data());

        /*
         * auto result = std::vector<float>{1, 5, 2, 6, 5, 9, 6, 10, 9, 13, 10, 14, 2, 6, 3, 7, 6, 10, 7, 11, 10, 14, 11, 15, 3,
                                   7, 4, 8, 7, 11, 8, 12, 11, 15, 12, 16};
         */
        auto result = std::vector<float>{1, 2, 5, 6, 2, 3, 6, 7, 3, 4, 7, 8, 5, 6, 9, 10, 6, 7, 10, 11, 7, 8, 11, 12, 9,
                                         10, 13, 14, 10, 11, 14, 15, 11, 12, 15, 16};
        REQUIRE(column == result);
        REQUIRE(std::equal(column.begin(), column.end(), result.begin()));
    }
}
