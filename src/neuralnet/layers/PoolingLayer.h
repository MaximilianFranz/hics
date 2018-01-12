//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <layerfunctions/LayerFunction.h>
#include "Layer.h"

class PoolingLayer : Layer{
protected:
    LayerFunction* function;

    std::vector<int> filterDimensions;
    int zeroPadding;
    int stride;
public:
    void forward(DataWrapper &input, DataWrapper &output) override;
};


