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

#include "ActivationLayer.h"



ActivationLayer::ActivationLayer(std::vector<int> &inputDimensions) {
    this->inputDimensions = inputDimensions;
    this->outputDimensions = calcOutputDimensions();
}

std::vector<int> ActivationLayer::calcOutputDimensions() {
    return inputDimensions; //Activation does not change the dimensions of the input.
}

void ActivationLayer::forward() {
    outputWrapper = new DataWrapper(getOutputDimensions());
    this->function->execute(*previousLayer->getOutputWrapper(), *outputWrapper);
    this->computed = true;
}

void ActivationLayer::setPlatform(Platform *platform) {
    this->function = platform->createActivationFunction(this->type);
    this->functionSet = true;
}

long long int ActivationLayer::getDifficulty() {
    inputWrapper = new DataWrapper(inputDimensions);
    if (this->difficulty == 0)
        this->difficulty = this->inputWrapper->getNumElements(); // Linear on input
    delete inputWrapper;
    return difficulty;
}



