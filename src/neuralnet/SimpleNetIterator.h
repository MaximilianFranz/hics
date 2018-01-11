//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include "NetIterator.h"

/**
 * forward declaration to avoid cyclic includes
 */
class NeuralNet;

class SimpleNetIterator : NetIterator {
private:
    const NeuralNet *net; // Why does this not recognize NeuralNet????
public:
    SimpleNetIterator(const NeuralNet *net);

    void first() override;

    void next() override;

    bool hasNext() override;

    Layer* getElement() override;

};




