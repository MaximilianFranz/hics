//
// Created by David Culley on 12.01.18.
//

#pragma once

#include <wrapper/DataWrapper.h>
#include <wrapper/WeightWrapper.h>

class ConvolutionFunction  {
public:
    virtual void execute(const DataWrapper &input,
                         DataWrapper &output,
                         const WeightWrapper &weights,
                         int stride,
                         int filterSize,
                         int numFilters,
                         int zeroPadding) = 0;
};


