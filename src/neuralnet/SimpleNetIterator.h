//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include "NetIterator.h"
#include "NeuralNet.h"

class SimpleNetIterator : NetIterator {
    const NeuralNet *net; // Why does this not recognize NeuralNet????
public:
    SimpleNetIterator(const NeuralNet *net);

    void first() override;

    void next() override;

    bool hasNext() override;

    Layer* getElement() override;

};




