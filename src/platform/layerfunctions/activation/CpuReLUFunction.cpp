//
// Created by michael on 15.01.18.
//

#include <algorithm>

#include "CpuReLUFunction.h"

void CpuReLUFunction::execute(const DataWrapper &input, DataWrapper &output) {
    auto *in = input.getDataArray();
    auto n = input.getNumElements();
    auto *out = output.getDataArray();

    for (int i = 0; i < n; i++) {
        *out = std::max(0.f, *in);
        out++;
        in++;
    }
}
