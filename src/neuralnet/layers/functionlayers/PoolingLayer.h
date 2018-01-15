//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <layerfunctions/LayerFunction.h>
#include <layerfunctions/pooling/PoolingFunction.h>
#include "layers/Layer.h"

class PoolingLayer : public Layer{
protected:
    PoolingFunction* function;

    int filterSize;
    int zeroPadding;
    int stride;
public:

    void forward(DataWrapper &input, DataWrapper &output) override;

    void setFunction(PoolingFunction* function);

    std::vector<int> calcOutputDimensions() override;
};


