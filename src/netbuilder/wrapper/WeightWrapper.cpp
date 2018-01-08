//
// Created by Maximilian Franz on 07.01.18.
//

#include "WeightWrapper.h"

//WeightWrapper::WeightWrapper(int numDimensions, int dimensionSizes, const std::vector &data) : Wrapper(numDimensions,
//                                                                                                       dimensionSizes,
//                                                                                                       data) {}

float WeightWrapper::getBias() const {
    return bias;
}

int WeightWrapper::getNumDimensions() {
    return Wrapper::getNumDimensions();
}

int WeightWrapper::getDimensionSizes() {
    return Wrapper::getDimensionSizes();
}
