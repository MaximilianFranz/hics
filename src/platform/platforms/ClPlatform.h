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

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include "CL/opencl.h"
#endif

#include "Platform.h"


class ClPlatform : public Platform {
private:
    cl_context context;
    cl_device_id device;
    ConvolutionFunction *c = nullptr;
    void init();

public:

    /**
     * Creates a function that performs the computations of an activation layer on a local OpenCL platform.
     * We use the ReLU activation function.
     *
     * @param type  The kind of activation function, e.g. the ReLU function
     * @return      A function that performs the computations of an activation layer by the specified activation @type
     */
    ActivationFunction *createActivationFunction(LayerType type) override;

    /**
     * Creates a function that performs the computations of a convolution layer on a local OpenCL platform.
     *
     * @return      A function that performs the computations of a convolutional layer
     */
    ConvolutionFunction *createConvolutionFunction() override;

    /**
     * Creates a function that performs the computations of a loss layer on a local OpenCL platform.
     * We use the softmax function.
     *
     * @param type  The kind of loss function, e.g. the softmax function
     * @return      A function that performs the computations of a loss layer by the specified loss @type
     */
    LossFunction *createLossFunction(LayerType type) override;

    /**
     * Creates a function that performs the computations of a pooling layer on a local OpenCL platform.
     * We use max-pooling.
     *
     * @param type  The kind of pooling function, e.g. max-pooling
     * @return      A function that performs the computations of a pooling layer by the specified pooling @type
     */
    PoolingFunction *createPoolingFunction(LayerType type) override;

    /**
     * Creates a function that performs the computations of a normalization layer on a local OpenCL platform.
     * We use local response normalization.
     *
     * @param type  The kind of normalization function, e.g. local response normalization
     * @return      A function that performs the computations of a normalization layer by the specified normalization @type
     */
    ResponseNormalizationFunction *createResponseNormalizationFunction(LayerType type) override;

    /**
     * Creates a function that performs the computations of a fully connected layer on a local OpenCL platform.
     *
     * @return      A function that performs the computations of a fully connected layer
     */
    FullyConnectedFunction *createFullyConnectedFunction() override;

    PlatformInfo &getPlatformInfo() override;

    explicit ClPlatform(PlatformInfo &info);

    ~ClPlatform();
};
