#include <vector>
#include <iostream>
#include <wrapper/ImageWrapper.h>
#include <util/im2col.h>

int main(int argc, char *argv[]) {
    int image_size = 3;
    int kernel_size = 2;
    int channels = 1;
    int padding = 0;
    int stride = 1;
    int output_size = (image_size - kernel_size + 2 * padding) / stride + 1;

    std::cout << "Image size: " << image_size << "x" << image_size << std::endl;
    std::cout << "Kernel size: " << kernel_size << "x" << kernel_size << std::endl;
    std::cout << "Padding: " << padding << std::endl;
    std::cout << "Output size: " << output_size << "x" << output_size << std::endl;

    auto image = std::vector<float>{1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto column = std::vector<float>();

    helper::im2col_cpu(image.data(), channels, image_size, image_size, kernel_size, padding, stride,
                       column.data());

    return 0;
}
