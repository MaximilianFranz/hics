//
// Created by michael on 15.01.18.
//

#pragma once

#include "PoolingFunction.h"

class CpuMaxPoolingFunction : public PoolingFunction {
public:
    void execute(const DataWrapper &input,
                 DataWrapper &output,
                 int stride,
                 int filterSize,
                 int zeroPadding) override;
};


