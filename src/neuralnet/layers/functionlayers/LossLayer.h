//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <layerfunctions/loss/LossFunction.h>
#include "layers/Layer.h"

/**
 * Super class For all loss layers implementing forward() and logic for output dimensions.
 */
class LossLayer : public Layer {
protected:
    LossFunction* function;
public:
    void setFunction(LossFunction* function);

    void forward(DataWrapper &input, DataWrapper &output) override;

    std::vector<int> calcOutputDimensions() override;
};

