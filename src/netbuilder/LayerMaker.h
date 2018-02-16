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

#include <layers/naive/InputLayer.h>
#include <layers/weightlayers/ConvolutionLayer.h>
#include <layers/functionlayers/MaxPoolingLayer.h>
#include <layers/functionlayers/LocalResponseNormLayer.h>
#include <layers/functionlayers/ReLUActivationLayer.h>
#include <layers/functionlayers/SoftMaxLossLayer.h>
#include <layers/weightlayers/FullyConnectedLayer.h>
#include "loader/ModelLoader.h"
#include "wrapper/WeightWrapper.h"



class LayerMaker {
private:

public:
    InputLayer* createInputLayer(LayerConstructionParams lcp);
    ConvolutionLayer* createConvLayer(LayerConstructionParams lcp, std::vector<int> inputDims, WeightWrapper* weights);
    MaxPoolingLayer* createMaxPoolLayer(LayerConstructionParams lcp, std::vector<int> inputDims);
    LocalResponseNormLayer* createLocalResponseNormLayer(LayerConstructionParams lcp, std::vector<int> inputDims);
    ReLUActivationLayer* createReLuActivationLayer(LayerConstructionParams lcp, std::vector<int> inputDims);
    SoftMaxLossLayer* createSoftmaxLossLayer(LayerConstructionParams lcp, std::vector<int> inputDims);
    FullyConnectedLayer* createFCLayer(LayerConstructionParams lcp, std::vector<int> inputDims, WeightWrapper* weights);

};