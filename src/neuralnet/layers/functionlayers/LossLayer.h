//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <layerfunctions/LayerFunction.h>
#include "layers/Layer.h"

class LossLayer : public Layer {
protected:
    LayerFunction* function;
public:
    void setFunction(LayerFunction* function);

    std::vector<int> calcOutputDimensions() override;
};

