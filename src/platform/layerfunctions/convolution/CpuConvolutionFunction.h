//
// Created by David Culley on 12.01.18.
//

#pragma once


#include "ConvolutionFunction.h"

class CpuConvolutionFunction : public ConvolutionFunction {
public:
    void execute(const DataWrapper &input,
                 DataWrapper &output,
                 const WeightWrapper &weights,
                 const WeightWrapper &bias,
                 int stride,
                 int filterSize,
                 int numFilters,
                 int zeroPadding) override;

};


