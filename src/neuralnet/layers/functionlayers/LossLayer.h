//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <layerfunctions/loss/LossFunction.h>
#include "layers/Layer.h"

class LossLayer : public Layer {
protected:
    LossFunction* function;
public:
    void setFunction(LossFunction* function);

    void forward() override;

    std::vector<int> calcOutputDimensions() override;

};

