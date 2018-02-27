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
