//
// Created by Maximilian Franz on 07.01.18.
//

#include "InputLayer.h"
#include "NotImplementedException.h"

void InputLayer::forward(DataWrapper &input, DataWrapper &output) {
    throw NotImplementedException();
}

InputLayer::InputLayer(std::vector<int> inputDimensions) {
    this->functionSet = true; // Naive Layers don't have functions
    this->type = "input";
    this->outputDimensions = calcOutputDimensions();

}

std::vector<int> InputLayer::calcOutputDimensions() {
    return inputDimensions; // Input layer does not change dimensions
}


