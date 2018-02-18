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

#include <layerfunctions/FullyConnectedFunction.h>
#include "layers/Layer.h"

/**
 * Layer representing a fully connected component of a neural net.
 * Holds its weight and bias.
 */
class FullyConnectedLayer : public Layer {
protected:
    FullyConnectedFunction* function;
    WeightWrapper* weights;

    DataWrapper* stretchInput(DataWrapper* input);

public:

    /**
     * Constructor for a FullyConnectedLayer without weights.
     *
     * Weights can be set afterwards.
     *
     * @param inputDimensions inputDimensions to this
     */
    explicit FullyConnectedLayer(std::vector<int> inputDimensions);

    /**
     * Constructor for a FullyConnectedLayer with weights
     *
     * @param inputDimensions
     * @param weights
     * @param bias
     */
    FullyConnectedLayer(std::vector<int> inputDimensions, WeightWrapper *weights);

    void forward() override;

    void setWeights(WeightWrapper* weights);


    void setFunction(FullyConnectedFunction* function);

    std::vector<int> calcOutputDimensions() override;
};


