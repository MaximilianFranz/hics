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
#include <IllegalArgumentException.h>


void LayerMaker::validateKernels(LayerConstructionParams lcp, std::string layerName){
    if (lcp.numFilters == 0) {
        throw IllegalArgumentException("The number of kernels should not be zero for " + layerName);
    }
}

InputLayer* LayerMaker::createInputLayer(LayerConstructionParams lcp){
    std::vector<int> inputDim = {lcp.inputChannels,
                                 lcp.inputSize,
                                 lcp.inputSize};
    InputLayer* input = new InputLayer(inputDim);
    return input;
}


ConvolutionLayer* LayerMaker::createConvLayer(LayerConstructionParams lcp, std::vector<int> inputDims, WeightWrapper* weights){
    LayerMaker::validateKernels(lcp, "Convolution layer");
    ConvolutionLayer* conv = new ConvolutionLayer(lcp.numFilters,
                                                  lcp.filterSize,
                                                  lcp.paddingSize,
                                                  lcp.stride,
                                                  lcp.numGroups,
                                                  inputDims,
                                                  weights);
    return conv;
}

MaxPoolingLayer* LayerMaker::createMaxPoolLayer(LayerConstructionParams lcp, std::vector<int> inputDims) {
    MaxPoolingLayer* maxPool = new MaxPoolingLayer(inputDims,
                                                   lcp.stride,
                                                   lcp.filterSize,
                                                   lcp.paddingSize);
    return maxPool;
}

LocalResponseNormLayer* LayerMaker::createLocalResponseNormLayer(LayerConstructionParams lcp, std::vector<int> inputDims) {
    LocalResponseNormLayer* localresp = new LocalResponseNormLayer(inputDims,
                                                                   lcp.normParams["radius"],
                                                                   lcp.normParams["alpha"],
                                                                   lcp.normParams["beta"],
                                                                   lcp.normParams["bias"]);
    return localresp;
}

ReLUActivationLayer* LayerMaker::createReLuActivationLayer(LayerConstructionParams lcp, std::vector<int> inputDims) {
    ReLUActivationLayer* relu = new ReLUActivationLayer(inputDims);
    return relu;
}

SoftMaxLossLayer* LayerMaker::createSoftmaxLossLayer(LayerConstructionParams lcp, std::vector<int> inputDims) {
    SoftMaxLossLayer* softmax = new SoftMaxLossLayer(inputDims);
    return softmax;
}

FullyConnectedLayer* LayerMaker::createFCLayer(LayerConstructionParams lcp, std::vector<int> inputDims, WeightWrapper* weights) {
    FullyConnectedLayer* fullycon = new FullyConnectedLayer(inputDims,
                                                            weights);
    return fullycon;
}