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
    this->weights = weights;
    this->outputDimensions = calcOutputDimensions();
    this->type = FULLYCONNECTED;
}

//TODO: Verify. This should
std::vector<int> FullyConnectedLayer::calcOutputDimensions() {
    std::vector<int> dim = {weights->getDimensions()[1]};
    return dim;
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

void FullyConnectedLayer::forward() {
    this->function->execute(*previousLayer->getOutputWrapper(), *outputWrapper, *weights);
    computed = true;
}


