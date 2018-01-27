//
// Created by Maximilian Franz on 07.01.18.
//

#include "SoftMaxLossLayer.h"



SoftMaxLossLayer::SoftMaxLossLayer(std::vector<int> &inputDimensions)
{
    this->inputDimensions = inputDimensions;
    this->type = LOSS_SOFTMAX;
    this->outputDimensions = inputDimensions;
    init(); // TODO never call virtual functions in constructor
}
