//
// Created by David Culley on 07.01.18.
//

#include "LayerMaker.h"
#include "../NotImplementedException.h"

InputLayer createInputLayer(LayerConstructionParams lcp){
    vector inputDim {lcp.inputSize, lcp.inputSize};
    return InputLayer(inputDim);
}

ConvolutionLayer createConvLayer(LayerConstructionParams lcp, WeightWrapper weights){
    throw NotImplementedException();
}

MaxPoolingLayer createMaxPoolLayer(LayerConstructionParams lcp) {
    throw NotImplementedException();
}

LocalResponseNormLayer createLocalResponseNormLayer(LayerConstructionParams lcp) {
    throw NotImplementedException();
}

ReLUActivationLayer createReLuActivationLayer(LayerConstructionParams lcp) {
    throw NotImplementedException();
}

SoftMaxLossLayer createSoftmaxLossLayer(LayerConstructionParams lcp) {
    throw NotImplementedException();
}

FullyConnectedLayer createFCLayer(LayerConstructionParams lcp, WeightWrapper weights) {
    throw NotImplementedException();
}
