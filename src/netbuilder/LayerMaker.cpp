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

#include <utility>

InputLayer* LayerMaker::createInputLayer(LayerConstructionParams &lcp){
    std::vector<int> inputDim = {lcp.inputChannels, lcp.inputSize, lcp.inputSize};
    auto input = new InputLayer(inputDim);
    return input;
}

ConvolutionLayer* LayerMaker::createConvLayer(LayerConstructionParams lcp, std::vector<int> inputDims, WeightWrapper* weights){
    auto conv = new ConvolutionLayer(lcp.numFilters,
                                                  lcp.filterSize,
                                                  lcp.paddingSize,
                                                  lcp.stride,
                                                  lcp.numGroups,
                                                  inputDims,
                                                  weights);
    return conv;
}

MaxPoolingLayer* LayerMaker::createMaxPoolLayer(LayerConstructionParams lcp, std::vector<int> inputDims) {
    auto maxPool = new MaxPoolingLayer(std::move(inputDims), lcp.stride, lcp.filterSize, lcp.paddingSize);
    return maxPool;
}

LocalResponseNormLayer* LayerMaker::createLocalResponseNormLayer(LayerConstructionParams lcp, std::vector<int> inputDims) {
    auto localresp = new LocalResponseNormLayer(std::move(inputDims),
                                                lcp.normParams["radius"],
                                                lcp.normParams["alpha"],
                                                lcp.normParams["beta"],
                                                lcp.normParams["bias"]);
    return localresp;
}

ReLUActivationLayer* LayerMaker::createReLuActivationLayer(LayerConstructionParams lcp, std::vector<int> inputDims) {
    auto relu = new ReLUActivationLayer(inputDims);
    return relu;
}

// Always return pointers to large objects because otherwise they would be copied every time.
SoftMaxLossLayer* LayerMaker::createSoftmaxLossLayer(LayerConstructionParams lcp, std::vector<int> inputDims) {
    auto softmax = new SoftMaxLossLayer(inputDims); // Create Layer with "new", so that scope handling is manual
    return softmax;
}

FullyConnectedLayer* LayerMaker::createFCLayer(LayerConstructionParams &lcp, std::vector<int> &inputDims, WeightWrapper* weights) {
    auto fullycon = new FullyConnectedLayer(std::move(inputDims), weights);
    return fullycon;
}



