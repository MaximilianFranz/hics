//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include "Layer.h"

class ActivationLayer : Layer {
public:
//    ActivationLayer(std::vector<int> inputDimensions);

    void forward(DataWrapper &input, DataWrapper &output) override;


protected:
};


