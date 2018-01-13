//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include "PoolingLayer.h"

class MaxPoolingLayer : public PoolingLayer{
public:
    MaxPoolingLayer(std::vector<int> inputDimensions, int stride, int filterSize, int zeroPadding);


};


