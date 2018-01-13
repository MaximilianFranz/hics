//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include "NormalizationLayer.h"

class LocalResponseNormLayer : public NormalizationLayer {
protected:
    float radius;
    float alpha;
    float beta;
    float bias;

public:
    LocalResponseNormLayer(std::vector<int> inputDimensions, float radius, float alpha, float beta, float bias);

    void forward(DataWrapper &input, DataWrapper &output) override;

    //GETTER

    float getRadius() const;

    float getAlpha() const;

    float getBeta() const;

    float getBias() const;
};

