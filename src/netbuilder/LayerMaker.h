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
    /**
     * Creates an input layer from given layer construction parameters.
     *
     * @param lcp an object of LayerConstructionParams type with all needed information for layer creation
     * @return a pointer to a new InputLayer object
     */
    InputLayer* createInputLayer(LayerConstructionParams lcp);

    /**
     * Creates a convolution layer from given layer construction parameters.
     *
     * @param lcp an object of LayerConstructionParams type with all needed information for layer creation
     * @param inputDims a number representing dimensions the images (data) have to have to be processed in the layer
     * @param weights a pointer to WeightWrapper object, that should be linked to the layer
     *
     * @return a pointer to a new ConvolutionLayer object
     */
    ConvolutionLayer* createConvLayer(LayerConstructionParams lcp, std::vector<int> inputDims, WeightWrapper* weights);

    /**
     * Creates a max pooling layer from given layer construction parameters.
     *
     * @param lcp an object of LayerConstructionParams type with all needed information for layer creation
     * @param inputDims a number representing dimensions the images (data) have to have to be processed in the layer
     *
     * @return a pointer to a new MaxPoolingLayer object
     */
    MaxPoolingLayer* createMaxPoolLayer(LayerConstructionParams lcp, std::vector<int> inputDims);

    /**
     * Creates a local response normalization layer from given layer construction parameters.
     *
     * @param lcp an object of LayerConstructionParams type with all needed information for layer creation
     * @param inputDims a number representing dimensions the images (data) have to have to be processed in the layer
     *
     * @return a pointer to a new LocalResponseNorm object
     */
    LocalResponseNormLayer* createLocalResponseNormLayer(LayerConstructionParams lcp, std::vector<int> inputDims);

    /**
     * Creates a rectified linear unit activation layer from given layer construction parameters.
     *
     * @param lcp an object of LayerConstructionParams type with all needed information for layer creation
     * @param inputDims a number representing dimensions the images (data) have to have to be processed in the layer
     *
     * @return a pointer to a new ReLuActivationLayer object
     */
    ReLUActivationLayer* createReLuActivationLayer(LayerConstructionParams lcp, std::vector<int> inputDims);

    /**
     * Creates a softmax loss layer from given layer construction parameters.
     *
     * @param lcp an object of LayerConstructionParams type with all needed information for layer creation
     * @param inputDims a number representing dimensions the images (data) have to have to be processed in the layer
     *
     * @return a pointer to a new SoftmaxLossLayer object
     */
    SoftMaxLossLayer* createSoftmaxLossLayer(LayerConstructionParams lcp, std::vector<int> inputDims);

    /**
     * Creates a fully connected layer from given layer construction parameters.
     *
     * @param lcp an object of LayerConstructionParams type with all needed information for layer creation
     * @param inputDims a number representing dimensions the images (data) have to have to be processed in the layer
     * @param weights a pointer to WeightWrapper object, that should be linked to the layer
     * 
     * @return a pointer to a new FCLayer object
     */
    FullyConnectedLayer* createFCLayer(LayerConstructionParams lcp, std::vector<int> inputDims, WeightWrapper* weights);

};