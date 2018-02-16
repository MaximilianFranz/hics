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

#include <string>

#include <layers/Layer.h>

#include <PlatformInfo.h>

#include <layerfunctions/pooling/PoolingFunction.h>
#include <layerfunctions/normalization/ResponseNormalizationFunction.h>
#include <layerfunctions/activation/ActivationFunction.h>
#include <layerfunctions/convolution/ConvolutionFunction.h>
#include <layerfunctions/loss/LossFunction.h>
#include <layerfunctions/FullyConnectedFunction.h>
#include "PlatformType.h"

class Platform {
protected:
    Platform() {};

    Platform(PlatformInfo &info) : platformInfo(info) {};

    PlatformInfo platformInfo;

public:
    virtual ActivationFunction *createActivationFunction(LayerType type) = 0;

    virtual ConvolutionFunction *createConvolutionFunction() = 0;

    virtual LossFunction *createLossFunction(LayerType type) = 0;

    virtual PoolingFunction *createPoolingFunction(LayerType type) = 0;

    virtual ResponseNormalizationFunction *createResponseNormalizationFunction(LayerType type) = 0;

    virtual FullyConnectedFunction *createFullyConnectedFunction() = 0;

    virtual PlatformInfo &getPlatformInfo() = 0;

    virtual PlatformType getPlatformType() = 0;
};
