//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <layerfunctions/LayerFunction.h>
#include <layerfunctions/loss/LossFunction.h>
#include "layers/Layer.h"

class LossLayer : public Layer {
protected:
    LossFunction* function;
public:
    void setFunction(LossFunction* function);

    std::vector<int> calcOutputDimensions() override;
};

