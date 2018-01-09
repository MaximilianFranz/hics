//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include "PoolingLayer.h"

class MaxPoolingLayer : PoolingLayer{
    void forward(DataWrapper input, DataWrapper output) override;

    bool isPlatformSet() override;

    bool isBiased() override;
};


