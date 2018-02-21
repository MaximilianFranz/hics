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

#include "PoolingLayer.h"


std::vector<int> PoolingLayer::calcOutputDimensions() {
    std::vector<int> outDim(3);
    outDim[D3_Z_DIM] = inputDimensions[0]; //number of channels remain the same!
    int outputWidth = (this->inputDimensions[D3_X_DIM] - filterSize) / stride + 1;
    outDim[D3_X_DIM] = outputWidth;
    outDim[D3_Y_DIM] = outputWidth;
    return outDim;
}

void PoolingLayer::forward() {
    outputWrapper = new DataWrapper(getOutputDimensions());
    this->function->execute(*previousLayer->getOutputWrapper(), *outputWrapper, stride, filterSize, zeroPadding);
    computed = true;
}

int PoolingLayer::getFilterSize() const {
    return filterSize;
}

int PoolingLayer::getZeroPadding() const {
    return zeroPadding;
}

int PoolingLayer::getStride() const {
    return stride;
}

void PoolingLayer::setPlatform(Platform *platform) {
    this->function = platform->createPoolingFunction(this->type);
    this->functionSet = true;
}
