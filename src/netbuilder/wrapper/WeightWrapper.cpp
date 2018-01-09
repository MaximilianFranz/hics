//
// Created by Maximilian Franz on 07.01.18.
//

#include "WeightWrapper.h"

float WeightWrapper::getBias() const {
    return bias;
}

int WeightWrapper::getNumDimensions() {
    return Wrapper::getNumDimensions();
}

int WeightWrapper::getDimensionSizes() {
    return Wrapper::getDimensionSizes();
}
