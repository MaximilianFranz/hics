//
// Created by michael on 15.01.18.
//

#include <NotImplementedException.h>

#include "CpuMaxPoolingFunction.h"

void CpuMaxPoolingFunction::execute(const DataWrapper &input,
                                    DataWrapper &output,
                                    int stride,
                                    int filterSize,
                                    int zeroPadding) {

    // TODO: check the following references if we can implement zeroPadding like this or need to change it
    // http://deeplearning.net/software/theano/tutorial/conv_arithmetic.html#full-padding
    // https://stackoverflow.com/questions/37674306/what-is-the-difference-between-same-and-valid-padding-in-tf-nn-max-pool-of-t/39371113#39371113
    // zeroPadding should probably be an enum: FULL, HALF(SAME), VALID (no padding),
    // the padding size is then determined automatically by the filter.
    // TODO: can we assume that filterSize is always square or should it have an x,y dimension?

    int numPlanes = input.getDimensions()[0];
    int numRows = input.getDimensions()[1];
    int numCols = input.getDimensions()[2];

    auto i = input.getDataArray();
    auto o = output.getDataArray();

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
                        float cur = i[index];
                        if (cur > max)
                            max = cur;

                    }
                }
                // store result and advance pointer
                *o = max;
                o++;

            }
        }
    }
}
