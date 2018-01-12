//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include "NormalizationLayer.h"

class LocalResponseNormLayer : NormalizationLayer {
protected:
    float radius;
    float alpha;
    float beta;
    float bias;

};

