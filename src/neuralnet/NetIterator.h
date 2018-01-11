//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <layers/Layer.h>
#include "NeuralNet.h"

/**
 * Provides an iterator interface that
 */
class NetIterator {
protected:
    int index;

public:
    virtual void first() = 0;
    virtual void next() = 0;
    virtual bool hasNext() = 0;
    virtual Layer* getElement() = 0;
};


