//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include "NormalizationLayer.h"

class LocalResponseNormLayer : NormalizationLayer {
    void forward(DataWrapper input, DataWrapper output) override;

    bool isPlatformSet() override;

    bool isBiased() override;
};

