//
// Created by David Culley on 07.01.18.
//

#pragma once

#include "loader/ModelLoader.h"
#include "wrapper/WeightWrapper.h"
#include "../neuralnet/layers/functionlayers/ActivationLayer.h"
#include "../neuralnet/layers/weightlayers/ConvolutionLayer.h"
#include "../neuralnet/layers/weightlayers/FullyConnectedLayer.h"
#include "../neuralnet/layers/naive/InputLayer.h"
#include "../neuralnet/layers/functionlayers/LocalResponseNormLayer.h"
#include "../neuralnet/layers/functionlayers/LossLayer.h"
#include "../neuralnet/layers/functionlayers/MaxPoolingLayer.h"
#include "../neuralnet/layers/functionlayers/ReLUActivationLayer.h"
#include "../neuralnet/layers/functionlayers/SoftMaxLossLayer.h"


class LayerMaker {
private:

public:
    InputLayer* createInputLayer(LayerConstructionParams lcp);
    ConvolutionLayer* createConvLayer(LayerConstructionParams lcp, WeightWrapper weights);
    MaxPoolingLayer* createMaxPoolLayer(LayerConstructionParams lcp);
    LocalResponseNormLayer* createLocalResponseNormLayer(LayerConstructionParams lcp);
    ReLUActivationLayer* createReLuActivationLayer(LayerConstructionParams lcp);
    SoftMaxLossLayer* createSoftmaxLossLayer(LayerConstructionParams lcp);
    FullyConnectedLayer* createFCLayer(LayerConstructionParams lcp, WeightWrapper weights);

};