//
// Created by Maximilian Franz on 17.01.18.
//

#include <LayerMaker.h>
#include <iostream>
#include <loader/JSONModelLoader.h>
#include "LayerMakerTest.h"


SCENARIO("Testing construction of Layers" , "[layermaker]") {

    LayerMaker l;
    std::string path ="../../../src/netbuilder/loader/alexnet.json";
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
        LayerConstructionParams lcp = m.getLayerConstructionParamsByIndex(1);
        REQUIRE(lcp.type == "conv");
        ConvolutionLayer* conv = l.createConvLayer(lcp, v, NULL);
        REQUIRE(conv->getInputDimensions() == v);
        REQUIRE(conv->getFilterSize() == 11);
        REQUIRE(conv->getStride() == 4);
        REQUIRE(conv->getNumFilters() == 96);
        REQUIRE(conv->getZeroPadding() == 0);
        REQUIRE(conv->calcOutputDimensions() == outputafter1stconv);
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
        LayerConstructionParams lcp = m.getLayerConstructionParamsByIndex(16);
        REQUIRE(lcp.type == "fullyConnected");
        REQUIRE(lcp.outputSize == 4096);
        //FullyConnectedLayer* fc = l.createFCLayer(lcp, inputforFC, NULL); can not be tested, cause calculateOutput() throws the
        //REQUIRE(fc->getInputDimensions() == inputforFC);                  notImplementedException
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