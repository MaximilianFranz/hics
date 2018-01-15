//
// Created by Maximilian Franz on 07.01.18.
//

#include "ActivationLayer.h"
#include "NotImplementedException.h"


void ActivationLayer::forward(DataWrapper &input, DataWrapper &output) {
    throw NotImplementedException();
}

std::vector<int> ActivationLayer::calcOutputDimensions() {
    return inputDimensions; //Activation does not change the dimensions of the input.
}

ActivationLayer::ActivationLayer(std::vector<int> &inputDimensions) {
    this->inputDimensions = inputDimensions;
    this->outputDimensions = calcOutputDimensions();
}

void ActivationLayer::setFunction(ActivationFunction *function) {
    this->function = function;
    functionSet = true;
}



