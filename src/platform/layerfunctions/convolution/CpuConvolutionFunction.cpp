//
// Created by David Culley on 12.01.18.
//

#include <NotImplementedException.h>

#include "CpuConvolutionFunction.h"

void CpuConvolutionFunction::execute(const DataWrapper &input,
                                     DataWrapper &output,
                                     const WeightWrapper &weights,
                                     int stride,
                                     int filterSize,
                                     int numFilters,
                                     int zeroPadding) {
    throw NotImplementedException();
}
