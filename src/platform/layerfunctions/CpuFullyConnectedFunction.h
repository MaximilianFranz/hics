//
// Created by michael on 15.01.18.
//

#pragma once


#include "FullyConnectedFunction.h"

class CpuFullyConnectedFunction : public FullyConnectedFunction {
public:
    void execute(const DataWrapper &input, DataWrapper &output, const WeightWrapper &weights,
                 const WeightWrapper &bias) override;
};


