//
// Created by David Culley on 07.01.18.
//

#pragma once

#include "loader/ModelLoader.h"
#include "wrapper/WeightWrapper.h"
#include "../neuralnet/layers/ActivationLayer.h"
#include "../neuralnet/layers/ConvolutionLayer.h"
#include "../neuralnet/layers/FullyConnectedLayer.h"
#include "../neuralnet/layers/InputLayer.h"
#include "../neuralnet/layers/LocalResponseNormLayer.h"
#include "../neuralnet/layers/LossLayer.h"
#include "../neuralnet/layers/MaxPoolingLayer.h"
#include "../neuralnet/layers/NormalizationLayer.h"
#include "../neuralnet/layers/PoolingLayer.h"
#include "../neuralnet/layers/ReLUActivationLayer.h"
#include "../neuralnet/layers/SoftMaxLossLayer.h"

class LayerMaker {
private:

public:
    InputLayer createInputLayer(LayerConstructionParams lcp);
    ConvolutionLayer createConvLayer(LayerConstructionParams lcp, WeightWrapper weights);
    MaxPoolingLayer createMaxPoolLayer(LayerConstructionParams lcp);
    LocalResponseNormLayer createLocalResponseNormLayer(LayerConstructionParams lcp);
    ReLUActivationLayer createReLuActivationLayer(LayerConstructionParams lcp);
    SoftMaxLossLayer createSoftmaxLossLayer(LayerConstructionParams lcp);
    FullyConnectedLayer createFCLayer(LayerConstructionParams lcp, WeightWrapper weights);

};
tu