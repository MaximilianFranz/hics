//
// Created by Maximilian Franz on 07.01.18.
//

#include "FullyConnectedLayer.h"
#include "NotImplementedException.h"



FullyConnectedLayer::FullyConnectedLayer(std::vector<int> inputDimensions) {
    this->inputDimensions = inputDimensions;
}

FullyConnectedLayer::FullyConnectedLayer(std::vector<int> inputDimensions, WeightWrapper *weights) {
    this->inputDimensions = inputDimensions;
    this->outputDimensions = calcOutputDimensions();
    this->weights = weights;
    this->type = FULLYCONNECTED;
}

void FullyConnectedLayer::forward(DataWrapper &input, DataWrapper &output) {
    throw NotImplementedException();
}

//TODO: Implement. Output size depends on the size of the weights
std::vector<int> FullyConnectedLayer::calcOutputDimensions() {
    throw NotImplementedException();
}

void FullyConnectedLayer::setWeights(WeightWrapper *weights) {
    this->weights = weights;
}


//TODO: Implement checks if the weights fit the layer!
bool FullyConnectedLayer::verifyWeights() {
    return false;
}

void FullyConnectedLayer::setFunction(FullyConnectedFunction *function) {
    this->function = function;
}


