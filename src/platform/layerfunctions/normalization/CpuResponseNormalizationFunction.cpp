//
// Created by michael on 15.01.18.
//

#include <cmath>

#include "CpuResponseNormalizationFunction.h"

void CpuResponseNormalizationFunction::execute(const DataWrapper &input,
                                               DataWrapper &output,
                                               float radius,
                                               float alpha,
                                               float beta,
                                               float bias) {

    int numPlanes = input.getDimensions().data()[0];
    int numRows = input.getDimensions().data()[1];
    int numCols = input.getDimensions().data()[2];

    auto in = input.getDataArray();
    auto out = output.getDataArray();

    for (int plane = 0; plane < numPlanes; plane++) {
        for (int row = 0; row < numRows; row++) {
            for (int col = 0; col < numCols; col++) {
                float sum = 0;
                float input = 0;
                for (int r = -radius; r <= radius; r++) {
                    if (plane + r < 0 || plane + r >= numPlanes) {
                        // skip regions which are outside of the image, the values are 0 and don't change sum
                        continue;
                    }

                    int index = (plane + r)*numCols*numRows + row*numCols + col;
                    float data = in[index];
                    sum += data*data;
                    // remember input value, so we don't have to compute the index again
                    if (r == 0) {
                        input = in[index];
                    }
                }
                float result = input / pow((bias + sum * alpha), beta);
                // store result and advance pointer
                *out = result;
                out++;
            }
        }
    }

}
