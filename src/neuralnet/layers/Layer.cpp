//
// Created by Maximilian Franz on 07.01.18.
//

#include "Layer.h"
#include "../../NotImplementedException.h"

bool Layer::isComputed() {
    return computed;
}

void Layer::setComputed(bool status) {
    computed = status;
}

bool Layer::isLayerFunctionSet() {
    return functionSet;
}

void Layer::reset() {
    this->functionSet = false;
    this->computed = false;

}


bool Layer::readyToCompute() {
    previousLayer->isComputed();
}

void Layer::init() {
    computed = false;
    functionSet = false;
}

std::vector<int> Layer::getOutputDimensions() {
    return outputDimensions;
}

Layer *Layer::getPreviousLayer() const {
    return previousLayer;
}

Layer *Layer::getNextLayer() const {
    return nextLayer;
}


const std::string &Layer::getType() const {
    return type;
}

const std::vector<int> &Layer::getInputDimensions() const {
    return inputDimensions;
}



