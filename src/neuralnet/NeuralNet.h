/* Copyright 2018 The HICS Authors
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall
 * be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <layers/Layer.h>
#include <layers/naive/InputLayer.h>
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

    /**
     *
     * @return last Layer of the network, which is the output.
     */
    const Layer *getLastLayer() const;
};


