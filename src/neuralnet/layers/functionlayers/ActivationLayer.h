//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <layerfunctions/activation/ActivationFunction.h>
#include "layers/Layer.h"

/**
 * A super class for activation layers implementing the forward() method and the logic for calculating
 * output dimensions.
 *
 */
class ActivationLayer : public Layer {
protected:
    ActivationFunction* function;
public:
    // TODO: This is not technically correct, because ActivationsLayer should not be instantiated.
    ActivationLayer(std::vector<int> &inputDimensions);

    void forward() override;

    std::vector<int> calcOutputDimensions() override;

    void setFunction(ActivationFunction* function);
};


