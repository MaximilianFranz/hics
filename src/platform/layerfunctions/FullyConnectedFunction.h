//
// Created by michael on 15.01.18.
//

#pragma once

#include <wrapper/DataWrapper.h>
#include <wrapper/WeightWrapper.h>

class FullyConnectedFunction {
public:
    virtual void execute(const DataWrapper &input,
                         DataWrapper &output,
                         const WeightWrapper &weights,
                         const WeightWrapper &bias) = 0;

};


