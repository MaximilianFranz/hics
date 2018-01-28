//
// Created by Maximilian Franz on 07.01.18.
//

#include "SimpleNetIterator.h"
#include "NeuralNet.h"

void SimpleNetIterator::first() {
    index = 0;
}

void SimpleNetIterator::next() {
    index++;
}

bool SimpleNetIterator::hasNext() {
    return (index != net->layers.size() - 1); //index not yet at last element!
}

Layer *SimpleNetIterator::getElement() {
    return net->layers[index];
}

SimpleNetIterator::SimpleNetIterator(const NeuralNet *net) : net(net) {
    this->index = 0;
}

