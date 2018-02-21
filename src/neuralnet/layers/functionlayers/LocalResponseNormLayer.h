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

#include <layerfunctions/normalization/ResponseNormalizationFunction.h>
#include <layers/Layer.h>

/**
 * Layer representing a ResponseNormalization operation.
 * It holds it's specific parameters and passes the computation on to the corresponding LayerFunction.
 */
class LocalResponseNormLayer : public Layer{
protected:
    float radius;
    float alpha;
    float beta;
    float bias;

    ResponseNormalizationFunction* function;

public:
    LocalResponseNormLayer(std::vector<int> inputDimensions, float radius, float alpha, float beta, float bias);

    std::vector<int> calcOutputDimensions() override;

    void forward() override;

    //GETTER and SETTER

    void setPlatform(Platform *platform) override;

    float getRadius() const;

    float getAlpha() const;

    float getBeta() const;

    float getBias() const;
};

