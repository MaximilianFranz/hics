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

#include "CpuMaxPoolingFunction.h"

void CpuMaxPoolingFunction::execute(const DataWrapper &input,
                                    DataWrapper &output,
                                    int stride,
                                    int filterSize,
                                    int zeroPadding) {

    // We handle zeroPadding differently, instead of symbolic specifiers, we pass
    // explicit values.

    // http://deeplearning.net/software/theano/tutorial/conv_arithmetic.html#full-padding
    // https://stackoverflow.com/questions/37674306/what-is-the-difference-between-same-and-valid-padding-in-tf-nn-max-pool-of-t/39371113#39371113
    // zeroPadding should probably be an enum: FULL, HALF(SAME), VALID (no padding),
    // the padding size is then determined automatically by the filter.

    // We assume that filters are always square, so we don't have an x and y filterSize.

    int numPlanes = input.getDimensions()[0];
    int numRows = input.getDimensions()[1];
    int numCols = input.getDimensions()[2];

    auto in = input.getDataArray();
    auto out = output.getDataArray();

    for (int plane = 0; plane < numPlanes; plane++) {
        for (int inRow = -zeroPadding; inRow < numRows+zeroPadding-filterSize+1; inRow += stride) {
            for (int inCol = -zeroPadding; inCol < numCols+zeroPadding-filterSize+1; inCol += stride) {
                float max = 0;

                for (int fRow = 0; fRow < filterSize; fRow++) {
                    if (inRow + fRow < 0 || inRow + fRow >= numRows) {
                        // skip regions which are outside of the image, the values are 0 and don't change max
                        continue;
                    }

                    for (int fCol = 0; fCol < filterSize; fCol++) {
                        if (inCol + fCol < 0 || inCol + fCol >= numCols) {
                            // skip regions which are outside of the image, the values are 0 and don't change max
                            continue;
                        }

                        // calculate index
                        int index = (inCol + fCol) + (inRow + fRow)*numCols + plane*numCols*numRows;
                        float cur = in[index];
                        if (cur > max)
                            max = cur;

                    }
                }
                // store result and advance pointer
                *out = max;
                out++;

            }
        }
    }
}
