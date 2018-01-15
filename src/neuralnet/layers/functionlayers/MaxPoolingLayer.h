//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include "PoolingLayer.h"

/**
 * Layer representing the max-pooling operation in a neural net
 * @inherit PoolingLayer
 */
class MaxPoolingLayer : public PoolingLayer{
public:
    MaxPoolingLayer(std::vector<int> inputDimensions, int stride, int filterSize, int zeroPadding);


};


