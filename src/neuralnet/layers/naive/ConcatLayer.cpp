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

#include <NotImplementedException.h>

#include <utility>
#include "ConcatLayer.h"


void ConcatLayer::setPreviousLayer(Layer *previousLayer) {
    previousLayerList.push_back(previousLayer);
}

// Default. This however does not make sense it just provides fail safety if requested.
Layer *ConcatLayer::getPreviousLayer() const {
    return previousLayerList.at(0);
}

ConcatLayer::ConcatLayer(std::vector<std::vector<int>> inputLayersDimensions) :
        inputLayersDimensions{std::move(inputLayersDimensions)} {
    this->type = LayerType::CONCAT;
    this->outputDimensions = calcOutputDimensions();
}

// This concatenates multiple layer dimensions by putting them "behind" each other in z dimension
std::vector<int> ConcatLayer::calcOutputDimensions() {
    std::vector<int> outDim(3, 0);
    for (auto inDim : inputLayersDimensions) {
        outDim[D3_Z_DIM] += inDim[D3_Z_DIM];
        outDim[D3_Y_DIM] = inDim[D3_Y_DIM];
        outDim[D3_X_DIM] = inDim[D3_X_DIM];
    }
    return outDim;
}

// TODO: Implement this in order to use GoogleNet.
// forward() adds up the input into one DataWrapper
void ConcatLayer::forward() {
    throw NotImplementedException();

}



