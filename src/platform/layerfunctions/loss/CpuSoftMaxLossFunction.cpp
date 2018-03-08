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

#include "CpuSoftMaxLossFunction.h"

void CpuSoftMaxLossFunction::execute(const DataWrapper &input, DataWrapper &output) {
    auto in = input.getDataArray();
    auto out = output.getDataArray();
    auto n = static_cast<int>(input.getNumElements());

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
