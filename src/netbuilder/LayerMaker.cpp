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
    vector inputDim {lcp.inputSize, lcp.inputSize};
    return MaxPoolingLayer(inputDim, lcp.stride, lcp.filterSize, lcp.paddingSize);
}

LocalResponseNormLayer createLocalResponseNormLayer(LayerConstructionParams lcp) {
    throw NotImplementedException();
}

ReLUActivationLayer createReLuActivationLayer(LayerConstructionParams lcp) {
    vector inputDim {lcp.inputSize, lcp.inputSize};
    return ReLUActivationLayer(inputDim);
}

SoftMaxLossLayer createSoftmaxLossLayer(LayerConstructionParams lcp) {
    vector inputDim {lcp.inputSize, lcp.inputSize};
    return SoftMaxLossLayer(inputDim);
}

FullyConnectedLayer createFCLayer(LayerConstructionParams lcp, WeightWrapper weights) {
    throw NotImplementedException();
}
