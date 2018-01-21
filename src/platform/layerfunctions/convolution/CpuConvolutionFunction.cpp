//
// Created by David Culley on 12.01.18.
//

#include <NotImplementedException.h>

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


    int halfFilterSize = (filterSize -1 ) / 2;
    int outSize = output.getDimensions()[1];
    int inSize = input.getDimensions()[1];
    int numPlanes = input.getDimensions()[0];

    for (int f = 0; f < numFilters; f++) {
        int skip = halfFilterSize - zeroPadding;
        for (int inRow = skip; inRow < inSize - skip; inRow += stride) {
            for (int inCol = skip; inCol < inSize - skip; inCol += stride) {
                float sum = 0;
                for (int plane = 0; plane < numPlanes; plane++) {
                    for (int fRow = -halfFilterSize; fRow <= halfFilterSize; fRow++) {
                        int row = inRow + fRow;
                        if (inRow + fRow < 0 || inRow + fRow >= inSize) {
                            // Skip regions which are outside of the image, the values are 0 and don't change sum
                            continue;
                        }
                        for (int fCol = -halfFilterSize; fCol <= halfFilterSize; fCol++) {

                            if (inCol + fCol < 0 || inCol + fCol  >= inSize) {
                                // Skip regions which are outside of the image, the values are 0 and don't change sum
                                continue;

                            }

                            int c = fCol + halfFilterSize;
                            int r = fRow + halfFilterSize;
                            int wIndex = c + r*filterSize + plane*filterSize*filterSize + f*numPlanes*filterSize*filterSize;
                            float weight = w[wIndex];

                            int iIndex = inCol + fCol + (inRow + fRow)*inSize +  + plane*inSize*inSize;
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
