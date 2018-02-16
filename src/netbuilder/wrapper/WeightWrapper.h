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

#include "Wrapper.h"

class WeightWrapper : public Wrapper {
private:
    std::vector<float> bias;
    std::vector<int> biasDimension;

public:

    /** Create WeightWrapper by passing weight and bias data vectors
     *
     * @param numDimensions
     * @param dimensions
     * @param weights
     * @param bias
     * @param biasNumDimensions
     * @param biasDimensions
     */
    WeightWrapper(std::vector<int> dimensions, std::vector<float> &weights, std::vector<float> &bias,
                  std::vector<int> biasDimensions);



    /** Cover method for readability and semantics.
     *
     * @return
     */
    std::vector<float> getWeights();
    /**
     * \brief Cover method for readability and semantics. Calls the getDataArray().
     *
     * This is passed by reference from the vector and is mutable.
     *
     * @return pointer to the raw weight array of this WeightWrapper.
     */
    float* getWeightArray();

    /**
     *\brief Get a pointer to the raw float array containing the bias of this wrapper.
     *
     * This is passed by reference from the vector and is mutable.
     *
     * @return pointer to the raw bias array of this WeightWrapper.
     */
    const float* getBiasArray() const;

    /**
     * \brief returns the vector containing the bias of this WeightWrapper.
     *
     * @return the vector with the bias of this WeightWrapper.
     */
    std::vector<float> getBias();

    const std::vector<float> getBias() const;

    const std::vector<int> &getBiasDimension() const;
};
