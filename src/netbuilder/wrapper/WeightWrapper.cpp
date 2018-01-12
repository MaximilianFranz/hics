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

float *WeightWrapper::getBiasArray() {
    return &bias[0];
}

std::vector<float> WeightWrapper::getBias() {
    return bias;
}

WeightWrapper::WeightWrapper(std::vector<int> &dimensions, std::vector<float> &weights, std::vector<float> &bias,
                             std::vector<int> &biasDimensions)
        : Wrapper(dimensions, weights),
          bias(bias),
          biasDimensionSizes(biasDimensions) {

}
