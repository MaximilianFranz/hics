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

#pragma once

#include <layerfunctions/convolution/ConvolutionFunction.h>
#include "layers/Layer.h"


/**
 *  Layer representing a convolutional function in a neural net.
 *  This layer holds the weights and bias in a WeightWrapper and all relevant parameters for this operation.
 */
class ConvolutionLayer : public Layer {
protected:
    ConvolutionFunction* function;

    WeightWrapper* weights;

    int numFilters;
    int filterSize;
    int zeroPadding;
    int stride;
    int numGroups;

    // HELPER methods

    std::vector<int> splitDim(std::vector<int> in, int factor, int index);

    WeightWrapper *getSecondHalf(WeightWrapper *weights);

    DataWrapper *getSecondHalf(DataWrapper *input);

    void forwardSplit();

public:

    /**
     * Constructor with weights - preferred!
     *
     * @param numFilters
     * @param filterSize
     * @param zeroPadding
     * @param stride
     * @param inputDimensions
     * @param weights
     * @param bias
     */
    ConvolutionLayer(int numFilters,
                     int filterSize,
                     int zeroPadding,
                     int stride,
                     int numGroups,
                     std::vector<int> &inputDimensions,
                     WeightWrapper* weights);

    std::vector<int> calcOutputDimensions() override;

    void forward() override;

    void setPlatform(Platform *platform) override;

    int getDifficulty() override;

    // GETTER

    int getNumFilters() const;

    int getFilterSize() const;

    int getZeroPadding() const;

    int getStride() const;

    int getNumGroups() const;


};



