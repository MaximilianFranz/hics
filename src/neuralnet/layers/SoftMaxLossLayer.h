//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once


#include "Layer.h"

class SoftMaxLossLayer : public Layer {
public:
    void forward(DataWrapper &input, DataWrapper &output) override;

    bool isPlatformSet() override;

    bool isBiased() override;
};
