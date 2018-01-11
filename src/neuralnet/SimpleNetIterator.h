//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include "NetIterator.h"

class SimpleNetIterator : NetIterator {
    const NeuralNet *net; // Declare here for now, since in NetIterator.h it results in build-error for some reason..
public:
    SimpleNetIterator(const NeuralNet* net);

    void first() override;

    void next() override;

    bool hasNext() override;

    Layer* getElement() override;

};

