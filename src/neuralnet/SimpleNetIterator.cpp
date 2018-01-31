//
// Created by Maximilian Franz on 07.01.18.
//

#include "SimpleNetIterator.h"
#include "NeuralNet.h"

void SimpleNetIterator::first() {
    this->index = 0;
}

void SimpleNetIterator::next() {
    this->index++;
}

bool SimpleNetIterator::hasNext() {
    return (index < net->layers.size()); //index not yet at last element!
}

Layer *SimpleNetIterator::getElement() {
    return net->layers[index];
}

SimpleNetIterator::SimpleNetIterator(const NeuralNet *net) : net(net) {
    this->index = 0;
}

