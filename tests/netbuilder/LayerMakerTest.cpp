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

#include <LayerMaker.h>
#include <iostream>
#include <loader/JSONModelLoader.h>
#include "LayerMakerTest.h"
#include <loader/weightloader/AlexNetWeightLoader.h>


SCENARIO("Testing construction of Layers" , "[layermaker]") {

    LayerMaker l;
    std::string path = RES_DIR "models/alexnet.json";
    JSONModelLoader m(path);
    std::vector<int> v{3, 227, 227};
    std::vector<int> outputafter1stconv{96, 55, 55};
    std::vector<int> outputafter1stpool{96, 27, 27};
    std::vector<int> inputforFC{256, 6, 6};
    std::vector<int> inputforSoftmax{1000};

    SECTION("InputLayer") {
        LayerConstructionParams lcp = m.getLayerConstructionParamsByIndex(0);
        REQUIRE(lcp.type == "input");
        InputLayer* input = l.createInputLayer(lcp);
        REQUIRE(input->getInputDimensions() == v);
    }

    SECTION("ConvolutionLayer1") {
        AlexNetWeightLoader loader(RES_DIR "weights/alexnet_weights.h5");
        WeightWrapper *weights = loader.getWeights(WeightLoader::LayerIdentifier(0));
        LayerConstructionParams lcp = m.getLayerConstructionParamsByIndex(1);
        REQUIRE(lcp.type == "conv");
        ConvolutionLayer* conv = l.createConvLayer(lcp, v, weights);
        REQUIRE(conv->getInputDimensions() == v);
        REQUIRE(conv->getFilterSize() == 11);
        REQUIRE(conv->getStride() == 4);
        REQUIRE(conv->getNumFilters() == 96);
        REQUIRE(conv->getZeroPadding() == 0);
        REQUIRE(conv->calcOutputDimensions() == outputafter1stconv);
    }

    SECTION("ConvolutionLayer2") {
        AlexNetWeightLoader loader(RES_DIR "weights/alexnet_weights.h5");
        WeightWrapper *weights = loader.getWeights(WeightLoader::LayerIdentifier(1));
        LayerConstructionParams lcp = m.getLayerConstructionParamsByIndex(5);
        REQUIRE(lcp.type == "conv");
        ConvolutionLayer* conv = l.createConvLayer(lcp, v, weights);
        REQUIRE(conv->getNumGroups() == 2);
    }

    SECTION("ActivationLayer") {
        LayerConstructionParams lcp = m.getLayerConstructionParamsByIndex(2);
        REQUIRE(lcp.type == "activation");
        REQUIRE(lcp.actFctType == "relu");
        ReLUActivationLayer* reluact = l.createReLuActivationLayer(lcp, outputafter1stconv);
        REQUIRE(reluact->getInputDimensions() == outputafter1stconv);
        REQUIRE(reluact->getOutputDimensions() == outputafter1stconv);
    }

    SECTION("LocalResponseNormalizationLayer") {
        LayerConstructionParams lcp = m.getLayerConstructionParamsByIndex(3);
        REQUIRE(lcp.type == "LRN");
        LocalResponseNormLayer* lrnorm = l.createLocalResponseNormLayer(lcp, outputafter1stconv);
        REQUIRE(lrnorm->getInputDimensions() == outputafter1stconv);
        REQUIRE(lrnorm->getRadius() == 2);
        REQUIRE(lrnorm->getAlpha() == 0.00002f);
        REQUIRE(lrnorm->getBias() == 1.0);
        REQUIRE(lrnorm->getBeta() == 0.75);
        REQUIRE(lrnorm->getOutputDimensions() == outputafter1stconv);
    }

    SECTION("MaxPoolingLayer") {
        LayerConstructionParams lcp = m.getLayerConstructionParamsByIndex(4);
        REQUIRE(lcp.type == "maxpooling");
        MaxPoolingLayer* maxpool = l.createMaxPoolLayer(lcp, outputafter1stconv);
        REQUIRE(maxpool->getInputDimensions() == outputafter1stconv);
        REQUIRE(maxpool->getFilterSize() == 3);
        REQUIRE(maxpool->getStride() == 2);
        REQUIRE(maxpool->getZeroPadding() == 0);
        REQUIRE(maxpool->getOutputDimensions() == outputafter1stpool);
    }

    SECTION("FullyConnectedLayer") {
        AlexNetWeightLoader loader(RES_DIR "weights/alexnet_weights.h5");
        WeightWrapper *weights = loader.getWeights(WeightLoader::LayerIdentifier(5));
        LayerConstructionParams lcp = m.getLayerConstructionParamsByIndex(16);
        REQUIRE(lcp.type == "fullyConnected");
        REQUIRE(lcp.outputSize == 4096);
        FullyConnectedLayer* fc = l.createFCLayer(lcp, inputforFC, weights);
        REQUIRE(fc->getInputDimensions() == inputforFC);
    }

    SECTION("LossLayer") {
        LayerConstructionParams lcp = m.getLayerConstructionParamsByIndex(21);
        REQUIRE(lcp.type == "losslayer");
        REQUIRE(lcp.actFctType == "softmax");
        SoftMaxLossLayer* softmax = l.createSoftmaxLossLayer(lcp, inputforSoftmax);
        REQUIRE(softmax->getInputDimensions() == inputforSoftmax);
        REQUIRE(softmax->getOutputDimensions() == inputforSoftmax);
    }
}