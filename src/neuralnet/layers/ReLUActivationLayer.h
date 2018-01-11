//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include "ActivationLayer.h"

class ReLUActivationLayer : ActivationLayer{
private:
    //TODO: Store Params here, because LayerInfo does not need these.
    // Could do the same with all parameters, because it is obsolete saving them in LayerInfo.
    float radius;
    float alpha;
    float beta;
    float bias;
public:

    ReLUActivationLayer(std::vector<int> inputDimensions, std::vector<float> params);
};


