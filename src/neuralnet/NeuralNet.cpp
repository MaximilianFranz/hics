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

#include <iostream>
#include <utility>
#include "NeuralNet.h"

// Include SimpleIterator only here in cpp to avoid build errors due to cyclic dependencies
#include "SimpleNetIterator.h"

void NeuralNet::addLayer(Layer *layer) {
    layers.push_back(layer);
    //Linking last layer currently in the net and newly added layer
    layers.at(layers.size() - 2)->setNextLayer(layer);
    layer->setPreviousLayer(layers.at(layers.size() - 2));
}

SimpleNetIterator *NeuralNet::createIterator() const {
    return new SimpleNetIterator(this);
}

NetInfo NeuralNet::getInfo() {
    return info;
}

bool NeuralNet::isPlacementComplete() {
    for (Layer* l : layers) {
        if (!l->isPlatformSet()) {
            return false;
        }
    }
    return true;
}

NeuralNet::NeuralNet(InputLayer *input, NetInfo info) : info(std::move(info)) {
    layers.push_back(input);
}

const Layer *NeuralNet::getLastLayer() const {
    return layers[layers.size() - 1];
}

NeuralNet::~NeuralNet() {
    for (auto l : layers) {
        delete l;
    }

}

void NeuralNet::reset() {
    for (auto l : layers) {
        l->reset();
    }

}

long long NeuralNet::getTotalDifficulty() {
    long long total = 0;
    for (auto l : layers) {
        total += l->getDifficulty();
    }
    return total;
}

const int NeuralNet::getNumLayers() const {
    return (int)layers.size(); // number of layers are reasonably small
}
