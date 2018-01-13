//
// Created by Maximilian Franz on 07.01.18.
//

#include "LossLayer.h"
#include "NotImplementedException.h"


void LossLayer::setFunction(LayerFunction *function) {
    this->function = function;
}

std::vector<int> LossLayer::calcOutputDimensions() {
    return inputDimensions; // LossLayer don't change output size.
}
