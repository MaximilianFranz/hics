//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <layerfunctions/convolution/ConvolutionFunction.h>
#include "layers/Layer.h"


/**
 *  Layer representing a convolutional function in a neural net.
 *  This layer holds the weights and bias in a WeightWrapper and all relevant parameters for this operation.
 */
class ConvolutionLayer : public Layer {
protected:
    ConvolutionFunction* function;

    WeightWrapper* weights;

    int numFilters;
    int filterSize;
    int zeroPadding;
    int stride;
public:

    /**
     * Constructor without weights, since computation cannot be done immediately anyways and weights could be set
     * afterwards.
     *
     * @param numFilters
     * @param filterSize
     * @param zeroPadding
     * @param stride
     * @param inputDimensions
     */
    ConvolutionLayer(int numFilters,
                     int filterSize,
                     int zeroPadding,
                     int stride,
                     std::vector<int> &inputDimensions);

    /**
     * Constructor with weights - preferred!
     *
     * @param numFilters
     * @param filterSize
     * @param zeroPadding
     * @param stride
     * @param inputDimensions
     * @param weights
     * @param bias
     */
    ConvolutionLayer(int numFilters,
                     int filterSize,
                     int zeroPadding,
                     int stride,
                     std::vector<int> &inputDimensions,
                     WeightWrapper* weights);

    std::vector<int> calcOutputDimensions() override;

    void forward() override;

    void setWeights(WeightWrapper* weights);

    void setFunction(ConvolutionFunction* function);

    bool verifyWeights();


    // GETTER

    int getNumFilters() const;

    int getFilterSize() const;

    int getZeroPadding() const;

    int getStride() const;

};


