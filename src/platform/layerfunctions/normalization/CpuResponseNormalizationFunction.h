//
// Created by michael on 15.01.18.
//

#pragma once

#include "ResponseNormalizationFunction.h"

class CpuResponseNormalizationFunction : public ResponseNormalizationFunction {
public:
    void execute(const DataWrapper &input,
                 DataWrapper &output,
                 float radius,
                 float alpha,
                 float beta,
                 float bias) override;
};


