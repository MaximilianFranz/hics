//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <layerfunctions/LayerFunction.h>
#include "Layer.h"

class ConvolutionLayer : Layer {
protected:
    LayerFunction* function;

    int numFilters;
    std::vector<int> filterDimensions;
    int zeroPadding;
    int stride;
    bool biased;
public:
    void forward(DataWrapper &input, DataWrapper &output) override;
};


