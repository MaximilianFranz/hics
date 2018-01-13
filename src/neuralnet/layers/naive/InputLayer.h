//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include "layers/Layer.h"
#include "NaiveLayer.h"

class InputLayer : public NaiveLayer {
public:
    InputLayer(std::vector<int> inputDimensions);

    void forward(DataWrapper &input, DataWrapper &output) override;

    std::vector<int> calcOutputDimensions() override;
};

