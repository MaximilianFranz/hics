//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <layerfunctions/FullyConnectedFunction.h>
#include "layers/Layer.h"

class FullyConnectedLayer : public Layer {
protected:
    bool biased;
    FullyConnectedFunction* function;
    WeightWrapper* weights;
    WeightWrapper* bias;
public:

    /**
     * Constructor for a FullyConnectedLayer without weights.
     *
     * Weights can be set afterwards.
     *
     * @param inputDimensions inputDimensions to this
     */
    FullyConnectedLayer(std::vector<int> inputDimensions);

    /**
     * Constructor for a FullyConnectedLayer with weights
     *
     * @param inputDimensions
     * @param weights
     * @param bias
     */
    FullyConnectedLayer(std::vector<int> inputDimensions, WeightWrapper *weights, WeightWrapper *bias);

    void forward(DataWrapper &input, DataWrapper &output) override;

    void setWeights(WeightWrapper* weights);

    void setBias(WeightWrapper* bias);

    void setFunction(FullyConnectedFunction* function);

    bool verifyWeights();

    std::vector<int> calcOutputDimensions() override;
};


