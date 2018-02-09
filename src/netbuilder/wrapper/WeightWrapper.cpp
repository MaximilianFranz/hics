//
// Created by Maximilian Franz on 07.01.18.
//

#include "WeightWrapper.h"


std::vector<float> WeightWrapper::getWeights() {
    return std::vector<float>();
}

float *WeightWrapper::getWeightArray() {
    return getDataArray();
}

const float *WeightWrapper::getBiasArray() const {
    return &bias[0];
}

std::vector<float> WeightWrapper::getBias() {
    return bias;
}

const std::vector<float> WeightWrapper::getBias() const {
    return bias;
}

const std::vector<int> &WeightWrapper::getBiasDimension() const {
    return biasDimension;
}

WeightWrapper::WeightWrapper(std::vector<int> dimensions, std::vector<float> &weights, std::vector<float> &bias,
                             std::vector<int> biasDimensions)
        : Wrapper(dimensions, weights),
          bias(bias),
          biasDimension(biasDimensions) {
}
