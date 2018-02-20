//
// Created by David Culley on 07.01.18.
//

#include "LayerMaker.h"

InputLayer* LayerMaker::createInputLayer(LayerConstructionParams lcp){
    std::vector<int> inputDim = {lcp.inputChannels, lcp.inputSize, lcp.inputSize};
    InputLayer* input = new InputLayer(inputDim);
    return input;
}


ConvolutionLayer* LayerMaker::createConvLayer(LayerConstructionParams lcp, std::vector<int> inputDims, WeightWrapper* weights){
    ConvolutionLayer* conv = new ConvolutionLayer(lcp.numFilters,
                                                  lcp.filterSize,
                                                  lcp.paddingSize,
                                                  lcp.stride,
                                                  lcp.numGroups,
                                                  inputDims,
                                                  weights);
    return conv;
}

MaxPoolingLayer* LayerMaker::createMaxPoolLayer(LayerConstructionParams lcp, std::vector<int> inputDims) {
    MaxPoolingLayer* maxPool = new MaxPoolingLayer(inputDims,
                                                   lcp.stride,
                                                   lcp.filterSize,
                                                   lcp.paddingSize);
    return maxPool;
}

LocalResponseNormLayer* LayerMaker::createLocalResponseNormLayer(LayerConstructionParams lcp, std::vector<int> inputDims) {
    LocalResponseNormLayer* localresp = new LocalResponseNormLayer(inputDims,
                                                                   lcp.normParams["radius"],
                                                                   lcp.normParams["alpha"],
                                                                   lcp.normParams["beta"],
                                                                   lcp.normParams["bias"]);
    return localresp;
}

ReLUActivationLayer* LayerMaker::createReLuActivationLayer(LayerConstructionParams lcp, std::vector<int> inputDims) {
    ReLUActivationLayer* relu = new ReLUActivationLayer(inputDims);
    return relu;
}

SoftMaxLossLayer* LayerMaker::createSoftmaxLossLayer(LayerConstructionParams lcp, std::vector<int> inputDims) {
    SoftMaxLossLayer* softmax = new SoftMaxLossLayer(inputDims);
    return softmax;
}

FullyConnectedLayer* LayerMaker::createFCLayer(LayerConstructionParams lcp, std::vector<int> inputDims, WeightWrapper* weights) {
    FullyConnectedLayer* fullycon = new FullyConnectedLayer(inputDims,
                                                            weights);
    return fullycon;
}



