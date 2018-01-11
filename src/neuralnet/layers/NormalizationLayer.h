//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include "Layer.h"

class NormalizationLayer : Layer {
    bool isPlatformSet() override;

    bool isBiased() override;

    void forward(DataWrapper &input, DataWrapper &output) override;
};

