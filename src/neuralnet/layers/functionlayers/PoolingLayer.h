//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <layerfunctions/LayerFunction.h>
#include "layers/Layer.h"

class PoolingLayer : public Layer{
protected:
    LayerFunction* function;

    int filterSize;
    int zeroPadding;
    int stride;
public:

    void forward(DataWrapper &input, DataWrapper &output) override;

    void setFunction(LayerFunction* function);

    std::vector<int> calcOutputDimensions() override;
};


