//
// Created by David Culley on 07.01.18.
//

#include "LayerMaker.h"
#include "../NotImplementedException.h"

InputLayer* createInputLayer(LayerConstructionParams lcp){
    vector<int> inputDim {lcp.inputChannels, lcp.inputSize, lcp.inputSize};
    InputLayer* input = new InputLayer(inputDim);
    return input;
}

ConvolutionLayer* createConvLayer(LayerConstructionParams lcp, WeightWrapper* weights){
    std::vector<int> inputDim {lcp.inputChannels, lcp.inputSize, lcp.inputSize};
    ConvolutionLayer* conv = new ConvolutionLayer(lcp.numFilters, lcp.filterSize, lcp.paddingSize, lcp.stride,
    inputDim, weights);
    return conv;
}

MaxPoolingLayer* createMaxPoolLayer(LayerConstructionParams lcp) {
    std::vector<int> inputDim {lcp.inputChannels, lcp.inputSize, lcp.inputSize};
    MaxPoolingLayer* maxPool = new MaxPoolingLayer(inputDim, lcp.stride, lcp.filterSize, lcp.paddingSize);
    return maxPool;
}

LocalResponseNormLayer* createLocalResponseNormLayer(LayerConstructionParams lcp) {
    std::vector<int> inputDim {lcp.inputChannels, lcp.inputSize, lcp.inputSize};
    LocalResponseNormLayer* localresp = new LocalResponseNormLayer(inputDim, lcp.normParams["radius"],
                                                                   lcp.normParams["alpha"], lcp.normParams["beta"],
                                                                   lcp.normParams["bias"]);
    return localresp;
}

ReLUActivationLayer* createReLuActivationLayer(LayerConstructionParams lcp) {
    vector<int> inputDim {lcp.inputChannels, lcp.inputSize, lcp.inputSize};
    ReLUActivationLayer* relu = new ReLUActivationLayer(inputDim);
    return relu;
}

// Always return pointers to large objects because otherwise they would be copied every time.
SoftMaxLossLayer* createSoftmaxLossLayer(LayerConstructionParams lcp) {
    std::vector<int> inputDim = {lcp.inputChannels, lcp.inputSize, lcp.inputSize}; //is always {z,y,x}
    SoftMaxLossLayer* softmax = new SoftMaxLossLayer(inputDim); // Create Layer with "new", so that scope handling is manual
    return softmax;
}

FullyConnectedLayer* createFCLayer(LayerConstructionParams lcp, WeightWrapper* weights) {
    std::vector<int> inputDim = {lcp.inputChannels, lcp.inputSize, lcp.inputSize};
    FullyConnectedLayer* fullycon = new FullyConnectedLayer(inputDim, weights);
    return fullycon;
}
