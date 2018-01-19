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
    ConvolutionLayer* createConvLayer(LayerConstructionParams lcp, WeightWrapper* weights);
    MaxPoolingLayer* createMaxPoolLayer(LayerConstructionParams lcp);
    LocalResponseNormLayer* createLocalResponseNormLayer(LayerConstructionParams lcp);
    ReLUActivationLayer* createReLuActivationLayer(LayerConstructionParams lcp);
    SoftMaxLossLayer* createSoftmaxLossLayer(LayerConstructionParams lcp);
    FullyConnectedLayer* createFCLayer(LayerConstructionParams lcp, WeightWrapper* weights);

};