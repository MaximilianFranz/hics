//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <layerfunctions/LayerFunction.h>
#include "Layer.h"

class ActivationLayer : Layer {
protected:
    LayerFunction* function;
public:
//    ActivationLayer(std::vector<int> inputDimensions);

    void forward(DataWrapper &input, DataWrapper &output) override;


protected:
};


