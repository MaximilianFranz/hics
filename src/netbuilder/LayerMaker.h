//
// Created by David Culley on 07.01.18.
//

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