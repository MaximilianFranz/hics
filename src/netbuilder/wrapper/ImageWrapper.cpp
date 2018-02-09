//
// Created by Maximilian Franz on 07.01.18.
//

#include "ImageWrapper.h"

ImageWrapper::ImageWrapper(std::vector<int> &dimensions, std::string filepath)
        : Wrapper(dimensions), filepath(filepath) {
}

ImageWrapper::ImageWrapper(std::vector<int> dimensions, std::vector<float> &data, std::string filepath)
            : Wrapper(dimensions, data), filepath(filepath) {

}

const std::string ImageWrapper::getFilepath() const {
    return filepath;
}




