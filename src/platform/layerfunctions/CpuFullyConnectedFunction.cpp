//
// Created by michael on 15.01.18.
//

#include "CpuFullyConnectedFunction.h"

void CpuFullyConnectedFunction::execute(const DataWrapper &input,
                                        DataWrapper &output,
                                        const WeightWrapper &weights) {
    auto in = input.getDataArray();
    auto out = output.getDataArray();
    auto w = weights.getDataArray();
    auto b = weights.getBiasArray();

    int inSize = input.getNumElements();
    int outSize = output.getNumElements();

    for (int row = 0; row < outSize; row++) {
        float sum = 0;
        for (int col = 0; col < inSize; col++) {
            float data = in[col];
            float weight = w[row*inSize + col];
            sum += data*weight;
        }
        // Add bias
        sum += b[row];
        // Store result and advance pointer
        *out = sum;
        out++;
    }
}
