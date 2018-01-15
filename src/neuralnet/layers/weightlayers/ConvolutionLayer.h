//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <layerfunctions/convolution/ConvolutionFunction.h>
#include "layers/Layer.h"


/**
 * Has Weights! -> Maybe one abstraction for Conv and Fully -> WeightLayer?
 */
class ConvolutionLayer : public Layer {
protected:
    ConvolutionFunction* function;

    WeightWrapper* weights;
    WeightWrapper* bias;

    int numFilters;
    int filterSize;
    int zeroPadding;
    int stride;
    bool biased;
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
                     WeightWrapper* weights,
                     WeightWrapper* bias);

    std::vector<int> calcOutputDimensions() override;

    void forward(DataWrapper &input, DataWrapper &output) override;

    void setWeights(WeightWrapper* weights);

    void setBias(WeightWrapper* bias);

    void setFunction(ConvolutionFunction* function);

    bool verifyWeights();


    // GETTER

    int getNumFilters() const;

    int getFilterSize() const;

    int getZeroPadding() const;

    int getStride() const;

};


