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

#include "LocalResponseNormLayer.h"


LocalResponseNormLayer::LocalResponseNormLayer(std::vector<int> inputDimensions, float radius, float alpha, float beta,
                                               float bias)

        :
          radius(radius),
          alpha(alpha),
          beta(beta),
          bias(bias)
{
    this->inputDimensions = inputDimensions;
    this->outputDimensions = calcOutputDimensions();
    this->type = NORMALIZATION_LOCALRESPONSE;
    this->init(); // TODO never call virtual functions in constructor
}

std::vector<int> LocalResponseNormLayer::calcOutputDimensions() {
    // Normalization does not change input dimensions
    return inputDimensions;
}

void LocalResponseNormLayer::forward() {
    outputWrapper = new DataWrapper(getOutputDimensions());
    this->function->execute(*previousLayer->getOutputWrapper(), *outputWrapper, radius, alpha, beta, bias);
    computed = true;
}

// GETTER and SETTER methods

float LocalResponseNormLayer::getRadius() const {
    return radius;
}

float LocalResponseNormLayer::getAlpha() const {
    return alpha;
}

float LocalResponseNormLayer::getBeta() const {
    return beta;
}

float LocalResponseNormLayer::getBias() const {
    return bias;
}

void LocalResponseNormLayer::setPlatform(Platform *platform) {
    this->function = platform->createResponseNormalizationFunction(this->type);
    this->functionSet = true;
}

