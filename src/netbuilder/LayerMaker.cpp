//
// Created by David Culley on 07.01.18.
//

#include "LayerMaker.h"
#include "../NotImplementedException.h"

InputLayer* createInputLayer(LayerConstructionParams lcp){
    vector inputDim {lcp.inputSize, lcp.inputSize};
    return InputLayer(inputDim)*;
}

ConvolutionLayer* createConvLayer(LayerConstructionParams lcp, WeightWrapper weights){
    throw NotImplementedException();
}

MaxPoolingLayer* createMaxPoolLayer(LayerConstructionParams lcp) {
    vector inputDim {lcp.inputSize, lcp.inputSize};
    return MaxPoolingLayer(inputDim, lcp.stride, lcp.filterSize, lcp.paddingSize)*;
}

LocalResponseNormLayer* createLocalResponseNormLayer(LayerConstructionParams lcp) {
    throw NotImplementedException();
}

ReLUActivationLayer* createReLuActivationLayer(LayerConstructionParams lcp) {
    vector inputDim {lcp.inputSize, lcp.inputSize};
    ReLUActivationLayer* relu = (new ReLUActivationLayer(inputDim));
    return relu;
}

// Always return pointers to large objects because otherwise they would be copied every time.
SoftMaxLossLayer* createSoftmaxLossLayer(LayerConstructionParams lcp) {
    std::vector<int> inputDim = {lcp.inputChannels, lcp.inputSize, lcp.inputSize}; //is always {z,y,x}
    SoftMaxLossLayer* softmax = new SoftMaxLossLayer(inputDim); // Create Layer with "new", so that scope handling is manual
    SoftMaxLossLayer s(inputDim);   // NOT like this, because 's' would be deleted once method ends and we would return a pointer to something
    return &s;                      // that does not exist
}

FullyConnectedLayer* createFCLayer(LayerConstructionParams lcp, WeightWrapper weights) {
    throw NotImplementedException();
}
