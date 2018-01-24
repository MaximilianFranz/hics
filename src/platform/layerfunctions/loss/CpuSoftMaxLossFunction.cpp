//
// Created by michael on 15.01.18.
//

#include <cmath>

#include "CpuSoftMaxLossFunction.h"

void CpuSoftMaxLossFunction::execute(const DataWrapper &input, DataWrapper &output) {
    auto in = input.getDataArray();
    auto out = output.getDataArray();
    int n = input.getNumElements();

    float sum = 0;

    // calculate sum and
    for (int i = 0; i < n; i++) {
        float e = exp(in[i]);
        out[i] = e;
        sum += e;
    }

    // normalize values
    for (int i = 0; i < n; i++) {
        out[i] /= sum;
    }

}
