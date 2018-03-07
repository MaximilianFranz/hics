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

#include <IllegalArgumentException.h>

#include <layerfunctions/loss/CpuSoftMaxLossFunction.h>
#include <layerfunctions/normalization/CpuResponseNormalizationFunction.h>
#include <layerfunctions/CpuFullyConnectedFunction.h>
#include <layerfunctions/pooling/CpuMaxPoolingFunction.h>
#include <layerfunctions/activation/CpuReLUFunction.h>
#include <layerfunctions/convolution/ClConvolutionFunction.h>

#include "AOCL_Utils.h"

#include "ClPlatform.h"


ActivationFunction *ClPlatform::createActivationFunction(LayerType type) {
    switch (type) {
        case LayerType::ACTIVATION_RELU:
            return new CpuReLUFunction();
        default:
            throw IllegalArgumentException();
    }
}

ConvolutionFunction *ClPlatform::createConvolutionFunction() {
    if (c == nullptr) {
        c = new ClConvolutionFunction(context, device);
    }
    return c;
}

LossFunction *ClPlatform::createLossFunction(LayerType type) {
    switch (type) {
        case LayerType::LOSS_SOFTMAX:
            return new CpuSoftMaxLossFunction();
        default:
            throw IllegalArgumentException();
    }
}

PoolingFunction *ClPlatform::createPoolingFunction(LayerType type) {
    switch (type) {
        case LayerType::POOLING_MAX:
            return new CpuMaxPoolingFunction();
        default:
            throw IllegalArgumentException();
    }
}

ResponseNormalizationFunction *ClPlatform::createResponseNormalizationFunction(LayerType type) {
    switch (type) {
        case LayerType::NORMALIZATION_LOCALRESPONSE:
            return new CpuResponseNormalizationFunction();
        default:
            throw IllegalArgumentException();
    }
}

FullyConnectedFunction *ClPlatform::createFullyConnectedFunction() {
    return new CpuFullyConnectedFunction();
}

PlatformInfo &ClPlatform::getPlatformInfo() {
    return this->platformInfo;
}

ClPlatform::ClPlatform(PlatformInfo &info) : Platform(info) {
    init();
}

void ClPlatform::init() {

    cl_int status = 0;
    cl_platform_id platform = 0;

    status = clGetPlatformIDs(1, &platform, NULL);
    aocl_utils::checkError(status, "Query for platform ids failed");

    device = 0;
    if(platformInfo.getType() == PlatformType::GPU) {
        status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL); // LCOV_EXCL_LINE
    } else if (platformInfo.getType() == PlatformType::CL_CPU) {
        status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &device, NULL);
    } else {
        // TODO: throw exception?
    }
    aocl_utils::checkError(status, "Query for device ids failed");

    context = clCreateContext(NULL, 1, &device, NULL, NULL, &status);
    aocl_utils::checkError(status, "Failed to create context");
}

ClPlatform::~ClPlatform() {
    clReleaseContext(context);
}

// Make AOCL_Utils happy
void cleanup() {}; // LCOV_EXCL_LINE
