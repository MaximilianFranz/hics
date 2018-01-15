//
// Created by michael on 15.01.18.
//

#pragma once

#include <wrapper/DataWrapper.h>
#include "LossFunction.h"

class CpuSoftMaxLossFunction : public LossFunction {
public:
    void execute(const DataWrapper &input, DataWrapper &output) override;

};


