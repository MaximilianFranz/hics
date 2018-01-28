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
    deleteGarbage(); //TODO: Does this fail if pointers already deleted?
}


bool Layer::readyToCompute() {
    return previousLayer->isComputed();
}

void Layer::init() {
    computed = false;
    functionSet = false;
}

std::vector<int> Layer::getOutputDimensions() const{
    return outputDimensions;
}

Layer *Layer::getPreviousLayer() const {
    return previousLayer;
}

Layer *Layer::getNextLayer() const {
    return nextLayer;
}


const std::vector<int> &Layer::getInputDimensions() const {
    return inputDimensions;
}

void Layer::setPreviousLayer(Layer *previousLayer) {
    Layer::previousLayer = previousLayer;
}

void Layer::setNextLayer(Layer *nextLayer) {
    Layer::nextLayer = nextLayer;
}

LayerType Layer::getType() const {
    return type;
}

DataWrapper *Layer::getInputWrapper() const {
    return inputWrapper;
}

void Layer::setInputWrapper(DataWrapper *inputWrapper) {
    Layer::inputWrapper = new DataWrapper(*(inputWrapper));
}

DataWrapper *Layer::getOutputWrapper() const {
    return outputWrapper;
}

void Layer::setOutputWrapper(DataWrapper *outputWrapper) {
    Layer::outputWrapper = outputWrapper;
}

void Layer::deleteGarbage() {
    if(this->type != LayerType::INPUT) {
        // TODO Maybe implement Garbe-collection manually
    }
}



