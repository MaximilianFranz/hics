//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <layerfunctions/normalization/ResponseNormalizationFunction.h>
#include <layers/Layer.h>

class LocalResponseNormLayer : public Layer{
protected:
    float radius;
    float alpha;
    float beta;
    float bias;

    ResponseNormalizationFunction* function;

public:
    LocalResponseNormLayer(std::vector<int> inputDimensions, float radius, float alpha, float beta, float bias);

    void forward(DataWrapper &input, DataWrapper &output) override;

    void setFunction(ResponseNormalizationFunction *function);


    //GETTER

    float getRadius() const;

    float getAlpha() const;

    float getBeta() const;

    float getBias() const;
};

