//
// Created by Maximilian Franz on 07.01.18.
//

#include "LossLayer.h"
#include "NotImplementedException.h"


std::vector<int> LossLayer::calcOutputDimensions() {
    return inputDimensions; // LossLayer don't change output size.
}

void LossLayer::setFunction(LossFunction *function) {
    this->function = function;
    this->functionSet = true;
}
