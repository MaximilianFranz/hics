//
// Created by Maximilian Franz on 07.01.18.
//

#include "SoftMaxLossLayer.h"
#include "NotImplementedException.h"


void SoftMaxLossLayer::forward(DataWrapper &input, DataWrapper &output) {
    throw NotImplementedException();
}

SoftMaxLossLayer::SoftMaxLossLayer(std::vector<int> &inputDimensions)
{
    this->inputDimensions = inputDimensions;
    this->type = "softmax";
    this->outputDimensions = inputDimensions;
    init();
}
