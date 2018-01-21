//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <layerfunctions/FullyConnectedFunction.h>
#include "layers/Layer.h"

/**
 * Layer representing a fully connected component of a neural net.
 * Holds its weight and bias.
 */
class FullyConnectedLayer : public Layer {
protected:
    FullyConnectedFunction* function;
    WeightWrapper* weights;
public:

    /**
     * Constructor for a FullyConnectedLayer without weights.
     *
     * Weights can be set afterwards.
     *
     * @param inputDimensions inputDimensions to this
     */
    explicit FullyConnectedLayer(std::vector<int> inputDimensions);

    /**
     * Constructor for a FullyConnectedLayer with weights
     *
     * @param inputDimensions
     * @param weights
     * @param bias
     */
    FullyConnectedLayer(std::vector<int> inputDimensions, WeightWrapper *weights);

    void forward() override;

    void setWeights(WeightWrapper* weights);


    void setFunction(FullyConnectedFunction* function);

    bool verifyWeights();

    std::vector<int> calcOutputDimensions() override;
};


