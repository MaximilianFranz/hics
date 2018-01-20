//
// Created by Maximilian Franz on 07.01.18.
//

#include "InputLayer.h"
#include "NotImplementedException.h"

InputLayer::InputLayer(std::vector<int> inputDimensions) {
    this->functionSet = true; // Naive Layers don't have functions
    this->type = INPUT;
    this->outputDimensions = calcOutputDimensions();

}

std::vector<int> InputLayer::calcOutputDimensions() {
    return inputDimensions; // Input layer does not change dimensions
}

void InputLayer::forward() {
    this->outputWrapper = inputWrapper; //In inputWrapper the input must be explicitly set!
}


