#include "im2colTest.h"

#include <iostream>
#include <util/im2col.h>

TEST_CASE("3x3x1 image and 3x3x1 kernel") {
    int image_size = 3;
    int kernel_size = 3;
    int channels = 1;
    int padding = 0;
    int stride = 1;
    int output_size = (image_size - kernel_size + 2 * padding) / stride + 1;
    auto image = std::vector<float>{1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto column = std::vector<float>(
            static_cast<unsigned long>(kernel_size * kernel_size * channels * output_size * output_size));

    helper::im2col_cpu(image.data(), channels, image_size, image_size, kernel_size, padding, stride, column.data());

    REQUIRE(column == std::vector<float>{1, 2, 3, 4, 5, 6, 7, 8, 9});
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
        auto image = std::vector<float>{1, 2, 3, 4, 5, 6, 7, 8, 9};

        helper::im2col_cpu(image.data(), channels, image_size, image_size, kernel_size, padding, stride, column.data());

        REQUIRE(column == std::vector<float>{1, 2, 4, 5, 2, 3, 5, 6, 4, 5, 7, 8, 5, 6, 8, 9});
    }

    SECTION("") {
        auto image = std::vector<float>{5, 1, 0, 2, 9, 5, 8, 1, 4};

        helper::im2col_cpu(image.data(), channels, image_size, image_size, kernel_size, padding, stride, column.data());

        REQUIRE(column == std::vector<float>{5, 1, 2, 9, 1, 0, 9, 5, 2, 9, 8, 1, 9, 5, 1, 4});
    }
}
