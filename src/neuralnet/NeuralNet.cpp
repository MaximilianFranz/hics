//
// Created by Maximilian Franz on 07.01.18.
//

#include "NeuralNet.h"

// Include SimpleIterator only here in cpp to avoid build errors due to cyclic dependencies
#include "SimpleNetIterator.h"

void NeuralNet::addLayer(Layer *layer) {
    layers.push_back(layer);
}

SimpleNetIterator *NeuralNet::createIterator() const {
    return new SimpleNetIterator(this);
}

NetInfo NeuralNet::getInfo() {
    return info;
}

bool NeuralNet::isComputationComplete() {
    for (Layer* l : layers) {
        if (!l->isComputed())
            return false;
    }
    return true;
    // Alternatively: return (layers[last].isComputed())
    // Can we guarantee consistency?
}

bool NeuralNet::isPlacementComplete() {
    for (Layer* l : layers) {
        if (!l->isLayerFunctionSet()) {
            return false;
        }
    }
}

bool NeuralNet::verifyConsistency() {
    SimpleNetIterator it(this);
    while (it.hasNext()) {
        if (it.getElement()->getOutputDimensions() != it.getElement()->getNextLayer()->getInputDimensions())
            return false;
    }
    return true;
}
