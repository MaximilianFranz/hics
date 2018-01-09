//
// Created by Maximilian Franz on 07.01.18.
//

#include "ImageWrapper.h"

const std::string &ImageWrapper::getFilepath() const {
    return filepath;
}

int ImageWrapper::getNumDimensions() {
    return Wrapper::getNumDimensions();
}

int ImageWrapper::getDimensionSizes() {
    return Wrapper::getDimensionSizes();
}
