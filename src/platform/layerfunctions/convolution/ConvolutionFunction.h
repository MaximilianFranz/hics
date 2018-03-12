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

#include <wrapper/DataWrapper.h>
#include <wrapper/WeightWrapper.h>

class ConvolutionFunction  {
public:

    /**
     * Performs the computations of a convolutional layer. Takes the @input and saves the results as @output.
     *
     * @param input         The input of the convolutional layer
     * @param output        The output of the convolutional layer
     * @param weights       The weights for the convolutional layer
     * @param stride        The stride for this layer
     * @param filterSize    The size of the filter for this layer
     * @param numFilters    The number of filters for this layer
     * @param zeroPadding   The padding for this layer
     */
    virtual void execute(const DataWrapper &input,
                         DataWrapper &output,
                         const WeightWrapper &weights,
                         int stride,
                         int filterSize,
                         int numFilters,
                         int zeroPadding) = 0;

    virtual ~ConvolutionFunction() = default;
};


