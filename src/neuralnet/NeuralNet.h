//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <layers/Layer.h>
#include <NetInfo.h>
#include <layers/naive/InputLayer.h>

/**
 * forward declaration to avoid cyclic includes.
 */
class SimpleNetIterator;

class NeuralNet {
private:
    NetInfo info;
    std::vector<Layer*> layers;


public:

    /**
     * Ensure that NeuralNet has an inputlayer, so layers can be added.
     *
     * @param input
     */
    NeuralNet(InputLayer *input, NetInfo info);

    friend class SimpleNetIterator;

    /**
     * Currently naive implementation to link the added layer to last layer in the net
     * TODO: To support multiple preceeding layers, this has to be changed and layer dependencies have
     * to be defined in the model and set by an advances NetBuilder.
     * @param layer
     */
    void addLayer(Layer* layer);


    NetInfo getInfo();

    bool isComputationComplete();

    bool isPlacementComplete();

    /**
     * TODO: Replace with NetIterator and get proper inheritance to work!
     *
     * @return an iterator
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


