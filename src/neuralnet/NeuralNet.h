//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <layers/Layer.h>
#include <NetInfo.h>

/**
 * forward declaration to avoid cyclic includes.
 */
class SimpleNetIterator;

class NeuralNet {
private:
    NetInfo info;
    std::vector<Layer*> layers;


public:
    friend class SimpleNetIterator;
    void addLayer(Layer* layer);

    NetInfo getInfo();

    bool isComputationComplete();

    bool isPlacementComplete();

    /**
     * TODO: Replace with NetIterator and get proper inheritance to work!
     *
     * @return
     */
    SimpleNetIterator* createIterator() const;

    /**
     * Iterates over the network and verifies that input and output dimensions of connected layers match.
     *
     * The network may not be computed, if this returns false.
     *
     * @return true if the dimensions match, false otherwise.
     */
    bool verifyConsistency();
};


