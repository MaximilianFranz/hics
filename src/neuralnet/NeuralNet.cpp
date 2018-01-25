//
// Created by Maximilian Franz on 07.01.18.
//

#include "NeuralNet.h"

// Include SimpleIterator only here in cpp to avoid build errors due to cyclic dependencies
#include "SimpleNetIterator.h"

void NeuralNet::addLayer(Layer *layer) {
    layers.push_back(layer);
    //Linking last layer currently in the net and newly added layer
    layers.at(layers.size() - 2)->setNextLayer(layer);
    layer->setPreviousLayer(layers.at(layers.size() - 2));
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
    return true;
}

bool NeuralNet::verifyConsistency() {
    SimpleNetIterator it(this);
    while (it.hasNext()) {
        if (it.getElement()->getOutputDimensions() != it.getElement()->getNextLayer()->getInputDimensions())
            return false;

        it.next();
    }
    return true;
}

NeuralNet::NeuralNet(InputLayer *input, NetInfo info) : info(info) {
    layers.push_back(input);
}

const Layer *NeuralNet::getLastLayer() const {
    return layers[layers.size() - 1];
}
