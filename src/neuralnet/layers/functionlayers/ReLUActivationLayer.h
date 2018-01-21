//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include "layers/functionlayers/ActivationLayer.h"

/**
 * Layer representing the RELU activation function in a neural net.
 */
class ReLUActivationLayer : public ActivationLayer {
public:
    ReLUActivationLayer(std::vector<int> &inputDimension);

};


