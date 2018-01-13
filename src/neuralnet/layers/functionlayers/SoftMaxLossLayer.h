//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once


#include "LossLayer.h"

class SoftMaxLossLayer : public LossLayer {
public:
    SoftMaxLossLayer(std::vector<int> &inputDimensions);

    void forward(DataWrapper &input, DataWrapper &output) override;
};
