//
// Created by Maximilian Franz on 07.01.18.
//

#include "ImageWrapper.h"

//ImageWrapper::ImageWrapper(int numDimensions, int dimensionSizes, const std::vector &data,
//                           const std::string &filepath) : Wrapper(numDimensions, dimensionSizes, data),
//                                                          filepath(filepath) {}

const std::string &ImageWrapper::getFilepath() const {
    return filepath;
}
