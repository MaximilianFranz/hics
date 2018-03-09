/* Copyright 2018 The HICS Authors
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall
 * be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 */

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
