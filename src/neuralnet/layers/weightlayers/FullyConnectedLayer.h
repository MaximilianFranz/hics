//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <layerfunctions/LayerFunction.h>
#include "layers/Layer.h"

class FullyConnectedLayer : public Layer {
protected:
    bool biased;
    LayerFunction* function;
    WeightWrapper* weights;
    WeightWrapper* bias;
public:

    FullyConnectedLayer(std::vector<int> inputDimensions);

    FullyConnectedLayer(std::vector<int> inputDimensions, WeightWrapper *weights, WeightWrapper *bias);

    void forward(DataWrapper &input, DataWrapper &output) override;

    void setWeights(WeightWrapper* weights);

    void setBias(WeightWrapper* bias);

    void setFunction(LayerFunction* function);

    bool verifyWeights();

    std::vector<int> calcOutputDimensions() override;
};


