//
// Created by Maximilian Franz on 07.01.18.
//

#include "NeuralNet.h"
#include "../NotImplementedException.h"

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
    return computationCompleted;
}

bool NeuralNet::isPlacementComplete() {
    return computationCompleted;
}
