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

#include "layers/Layer.h"
#include "NaiveLayer.h"

/**
 * Allows to concatenate multiple outputs from more than one previous layer into one.
 */
class ConcatLayer : public NaiveLayer {
protected:
    //TODO: This needs to implement the previous layer functions differently!
    std::vector<std::vector<int>> inputLayersDimensions;
    std::vector<Layer*> previousLayerList;
public:

    /**
     * Constructor for a ConcatLayer given the dimensions of all input layers.
     *
     * @param inputLayersDimensions dimensions of all layers that are concatenated by this layer.
     */
    ConcatLayer(std::vector<std::vector<int>> inputLayersDimensions);

    std::vector<int> calcOutputDimensions() override;

    void forward() override;

    void setPreviousLayer(Layer *previousLayer) override;

    Layer *getPreviousLayer() const override;

};


