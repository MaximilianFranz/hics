//
// Created by michael on 15.01.18.
//

#pragma once

#include "ActivationFunction.h"

class CpuReLUFunction : public ActivationFunction {
public:
    void execute(const DataWrapper &input, DataWrapper &output) override;

};


