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

#include "LayerMaker.h"

InputLayer* LayerMaker::createInputLayer(LayerConstructionParams &lcp){
    std::vector<int> inputDim = {lcp.inputChannels, lcp.inputSize, lcp.inputSize};
    return new InputLayer(inputDim);
}

//TODO: Do line-breaks everywhere like this!
ConvolutionLayer* LayerMaker::createConvLayer(LayerConstructionParams &lcp, std::vector<int> &inputDims, WeightWrapper* weights){
    return new ConvolutionLayer(lcp.numFilters,
                                                  lcp.filterSize,
                                                  lcp.paddingSize,
                                                  lcp.stride,
                                                  lcp.numGroups,
                                                  inputDims,
                                                  weights);
}

MaxPoolingLayer* LayerMaker::createMaxPoolLayer(LayerConstructionParams &lcp, std::vector<int> &inputDims) {
    return new MaxPoolingLayer(inputDims, lcp.stride, lcp.filterSize, lcp.paddingSize);
}

LocalResponseNormLayer* LayerMaker::createLocalResponseNormLayer(LayerConstructionParams &lcp, std::vector<int> &inputDims) {
    return new LocalResponseNormLayer(inputDims, lcp.normParams["radius"],
                                                                   lcp.normParams["alpha"], lcp.normParams["beta"],
                                                                   lcp.normParams["bias"]);
}

ReLUActivationLayer* LayerMaker::createReLuActivationLayer(LayerConstructionParams &lcp, std::vector<int> &inputDims) {
    return new ReLUActivationLayer(inputDims);
}

// Always return pointers to large objects because otherwise they would be copied every time.
SoftMaxLossLayer* LayerMaker::createSoftmaxLossLayer(LayerConstructionParams &lcp, std::vector<int> &inputDims) {
    return new SoftMaxLossLayer(inputDims); // Create Layer with "new", so that scope handling is manual
}

FullyConnectedLayer* LayerMaker::createFCLayer(LayerConstructionParams &lcp, std::vector<int> &inputDims, WeightWrapper* weights) {
    return new FullyConnectedLayer(inputDims, weights);
}



