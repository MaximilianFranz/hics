//
// Created by michael on 15.01.18.
//

#include <cmath>

#include "CpuSoftMaxLossFunction.h"

void CpuSoftMaxLossFunction::execute(const DataWrapper &input, DataWrapper &output) {
    auto in = input.getDataArray();
    auto out = output.getDataArray();
    int n = input.getNumElements();

    double sum = 0;

    float in_norm[n];
    double out_temp[n];

    //find max
    float max = 0;
    for (int a = 0; a < n; a++) {
        if(in[a] > max) {
            max = in[a];
        }
    }
    //substract max from all entries for numerical stability and normalize
    for (int b = 0; b < n; b++) {
        in_norm[b] = (in[b] - max);
    }
    // calculate sum and
    for (int i = 0; i < n; i++) {
        double e = (std::exp(in_norm[i]));
        out_temp[i] = e;
        sum += e;
    }

    // normalize values
    for (int i = 0; i < n; i++) {
        out[i] = static_cast<float>(out_temp[i] / sum); //is between 0 and 1
    }

}
