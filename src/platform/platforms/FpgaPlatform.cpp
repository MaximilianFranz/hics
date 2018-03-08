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
#include <layerfunctions/convolution/FpgaConvolutionFunction.h>

#include "AOCL_Utils.h"

#include "FpgaPlatform.h"


ActivationFunction *FpgaPlatform::createActivationFunction(LayerType type) {
    switch (type) {
        case LayerType::ACTIVATION_RELU:
            return new CpuReLUFunction();
        default:
            throw IllegalArgumentException();
    }
}

ConvolutionFunction *FpgaPlatform::createConvolutionFunction() {
    if (c == nullptr) {
        c = new FpgaConvolutionFunction(context, device);
    }
    return c;
}

LossFunction *FpgaPlatform::createLossFunction(LayerType type) {
    switch (type) {
        case LayerType::LOSS_SOFTMAX:
            return new CpuSoftMaxLossFunction();
        default:
            throw IllegalArgumentException();
    }
}

PoolingFunction *FpgaPlatform::createPoolingFunction(LayerType type) {
    switch (type) {
        case LayerType::POOLING_MAX:
            return new CpuMaxPoolingFunction();
        default:
            throw IllegalArgumentException();
    }
}

ResponseNormalizationFunction *FpgaPlatform::createResponseNormalizationFunction(LayerType type) {
    switch (type) {
        case LayerType::NORMALIZATION_LOCALRESPONSE:
            return new CpuResponseNormalizationFunction();
        default:
            throw IllegalArgumentException();
    }
}

FullyConnectedFunction *FpgaPlatform::createFullyConnectedFunction() {
    return new CpuFullyConnectedFunction();
}

PlatformInfo &FpgaPlatform::getPlatformInfo() {
    return this->platformInfo;
}

FpgaPlatform::FpgaPlatform(PlatformInfo &info) : Platform(info) {
    init();
}

void FpgaPlatform::init() {

    cl_int status = 0;
    cl_platform_id platform = 0;

    status = clGetPlatformIDs(1, &platform, NULL);
    aocl_utils::checkError(status, "Query for platform ids failed");

    device = 0;
    // We could filter for the platform name, but since the FpgaPlatform
    // is only available on the board, this is not strictly necessary, so we
    // just query for all available platforms.
    status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &device, NULL);
    aocl_utils::checkError(status, "Query for device ids failed");

    context = clCreateContext(NULL, 1, &device, NULL, NULL, &status);
    aocl_utils::checkError(status, "Failed to create context");
}

FpgaPlatform::~FpgaPlatform() {
    clReleaseContext(context);
}

// Make AOCL_Utils happy
void cleanup() {}; // LCOV_EXCL_LINE
