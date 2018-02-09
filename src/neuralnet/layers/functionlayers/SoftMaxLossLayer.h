//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once


#include "LossLayer.h"

/**
 * Layer representing a softmax loss function in a neural net.
 */
class SoftMaxLossLayer : public LossLayer {
public:
    explicit SoftMaxLossLayer(std::vector<int> &inputDimensions);
};
