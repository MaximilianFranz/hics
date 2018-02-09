//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <layerfunctions/pooling/PoolingFunction.h>
#include "layers/Layer.h"

/**
 * Super class for all pooling layers.
 */
class PoolingLayer : public Layer {
protected:
    PoolingFunction* function;

    int filterSize;
    int zeroPadding;
    int stride;
public:
    void forward() override;


    void setFunction(PoolingFunction* function);

    std::vector<int> calcOutputDimensions() override;

    // GETTER

    int getFilterSize() const;

    int getZeroPadding() const;

    int getStride() const;
};


