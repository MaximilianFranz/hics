
#pragma once


#include "ConvolutionFunction.h"

class FpgaConvolutionFunction : public ConvolutionFunction {
public:
    void execute(const DataWrapper &input,
                 DataWrapper &output,
                 const WeightWrapper &weights,
                 int stride,
                 int filterSize,
                 int numFilters,
                 int zeroPadding) override;

};


