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

#include "Layer.h"

bool Layer::isComputed() {
    return computed;
}

void Layer::setComputed(bool status) {
    computed = status;
}

bool Layer::isLayerFunctionSet() {
    return functionSet;
}

void Layer::reset() {
    this->functionSet = false;
    this->computed = false;
    deleteGarbage(); //TODO: Does this fail if pointers already deleted?
}


bool Layer::readyToCompute() {
    return previousLayer->isComputed();
}

void Layer::init() {
    computed = false;
    functionSet = false;
}

std::vector<int> Layer::getOutputDimensions() const{
    return outputDimensions;
}

Layer *Layer::getPreviousLayer() const {
    return previousLayer;
}

Layer *Layer::getNextLayer() const {
    return nextLayer;
}


const std::vector<int> &Layer::getInputDimensions() const {
    return inputDimensions;
}

void Layer::setPreviousLayer(Layer *previousLayer) {
    Layer::previousLayer = previousLayer;
}

void Layer::setNextLayer(Layer *nextLayer) {
    Layer::nextLayer = nextLayer;
}

LayerType Layer::getType() const {
    return type;
}

DataWrapper *Layer::getInputWrapper() const {
    return inputWrapper;
}

void Layer::setInputWrapper(DataWrapper *inputWrapper) {
    Layer::inputWrapper = new DataWrapper(*(inputWrapper));
}

DataWrapper *Layer::getOutputWrapper() const {
    return outputWrapper;
}

void Layer::setOutputWrapper(DataWrapper *outputWrapper) {
    Layer::outputWrapper = outputWrapper;
}

void Layer::deleteGarbage() {
    if(this->type != LayerType::INPUT) {
        delete previousLayer->getOutputWrapper();
    }
}



