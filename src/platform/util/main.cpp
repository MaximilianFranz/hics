#include <vector>
#include <iostream>
#include <wrapper/ImageWrapper.h>
#include <util/im2col.h>

int main(int argc, char *argv[]) {
    int image_size = 4;
    int kernel_size = 2;
    int channels = 1;
    int padding = 0;
    int stride = 1;
    int output_size = (image_size - kernel_size + 2 * padding) / stride + 1;

    std::cout << "Image size: " << image_size << "x" << image_size << std::endl;
    std::cout << "Kernel size: " << kernel_size << "x" << kernel_size << std::endl;
    std::cout << "Padding: " << padding << std::endl;

    std::cout << std::endl;
    std::cout << "Ergebnismatrix M:" << std::endl;
    std::cout << "Anzahl der Spalten: " << kernel_size * kernel_size << std::endl;
    std::cout << "Anzahl der Zeilen: " << output_size * output_size << std::endl;
    std::cout << std::endl;

    auto column = std::vector<float>(
            static_cast<unsigned long>(kernel_size * kernel_size * channels * output_size * output_size));

    auto image = std::vector<float>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

    std::cout << "Image: " << std::endl;
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

    helper::im2col_cpu(image.data(), channels, image_size, image_size, kernel_size, padding, stride, column.data());

    std::cout << "Ergebnismatrix: " << std::endl;
    counter = 0;
    for (std::vector<float>::const_iterator i = column.begin(); i != column.end(); ++i) {

        if (counter >= kernel_size * kernel_size * channels) {
            std::cout << std::endl;
            counter = 0;
        }

        std::cout << *i << ' ';
        counter++;
    }

    return 0;
}
