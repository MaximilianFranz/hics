//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include "Layer.h"

class ConvolutionLayer : Layer {
    void forward(DataWrapper input, DataWrapper output) override;

    bool isPlatformSet() override;

    bool isBiased() override;
};


