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

#include "CpuConvolutionFunction.h"

void CpuConvolutionFunction::execute(const DataWrapper &input,
                                     DataWrapper &output,
                                     const WeightWrapper &weights,
                                     int stride,
                                     int filterSize,
                                     int numFilters,
                                     int zeroPadding) {
    auto b = weights.getBiasArray();
    auto w = weights.getDataArray();
    auto i = input.getDataArray();
    auto o = output.getDataArray();


    // We assume filterSize is always odd
    int halfFilterSize = (filterSize -1 ) / 2;
    int numPlanes = input.getDimensions()[0];
    int numRows = input.getDimensions()[1];
    int numCols = input.getDimensions()[2];


    for (int f = 0; f < numFilters; f++) {
        int skip = halfFilterSize - zeroPadding;
        for (int inRow = skip; inRow < numRows - skip; inRow += stride) {
            for (int inCol = skip; inCol < numCols - skip; inCol += stride) {
                float sum = 0;
                for (int plane = 0; plane < numPlanes; plane++) {
                    for (int fRow = -halfFilterSize; fRow <= halfFilterSize; fRow++) {

                        if (inRow + fRow < 0 || inRow + fRow >= numRows) {
                            // Skip regions which are outside of the image, the values are 0 and don't change sum
                            continue;
                        }

                        for (int fCol = -halfFilterSize; fCol <= halfFilterSize; fCol++) {

                            if (inCol + fCol < 0 || inCol + fCol  >= numCols) {
                                // Skip regions which are outside of the image, the values are 0 and don't change sum
                                continue;
                            }

                            int c = fCol + halfFilterSize;
                            int r = fRow + halfFilterSize;
                            int wIndex = c + r*filterSize + plane*filterSize*filterSize + f*numPlanes*filterSize*filterSize;
                            float weight = w[wIndex];

                            int iIndex = (inCol + fCol) + (inRow + fRow)*numCols +  plane*numCols*numRows;
                            float data = i[iIndex];

                            sum += weight*data;
                        }

                    }

                }
                // Add bias
                sum += b[f];
                // Store result and advance pointer
                *o = sum;
                o++;

            }
        }
    }
}
