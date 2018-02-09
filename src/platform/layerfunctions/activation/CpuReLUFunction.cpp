//
// Created by michael on 15.01.18.
//

#include <algorithm>

#include "CpuReLUFunction.h"

void CpuReLUFunction::execute(const DataWrapper &input, DataWrapper &output) {
    auto in = input.getDataArray();
    auto out = output.getDataArray();
    auto n = input.getNumElements();

    for (int i = 0; i < n; i++) {
        out[i] = std::max(0.f, in[i]);
    }
}
