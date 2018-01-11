//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include "Layer.h"

class PoolingLayer : Layer{
    void forward(DataWrapper &input, DataWrapper &output);
};


