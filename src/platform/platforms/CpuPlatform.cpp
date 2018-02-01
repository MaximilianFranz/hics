//
// Created by David Culley on 12.01.18.
//

#include <NotImplementedException.h>
#include <IllegalArgumentException.h>

#include <layerfunctions/convolution/CpuConvolutionFunction.h>
#include <layerfunctions/loss/CpuSoftMaxLossFunction.h>
#include <layerfunctions/normalization/CpuResponseNormalizationFunction.h>
#include <layerfunctions/CpuFullyConnectedFunction.h>
#include <layerfunctions/pooling/CpuMaxPoolingFunction.h>
#include <layerfunctions/activation/CpuReLUFunction.h>

#include "CpuPlatform.h"


ActivationFunction *CpuPlatform::createActivationFunction(LayerType type) {
    switch (type) {
        case ACTIVATION_RELU:
            return new CpuReLUFunction();
        default:
            throw IllegalArgumentException();
    }
}

ConvolutionFunction *CpuPlatform::createConvolutionFunction() {
    return new CpuConvolutionFunction();
}

LossFunction *CpuPlatform::createLossFunction(LayerType type) {
    switch (type) {
        case LOSS_SOFTMAX:
            return new CpuSoftMaxLossFunction();
        default:
            throw IllegalArgumentException();
    }
}

PoolingFunction *CpuPlatform::createPoolingFunction(LayerType type) {
    switch (type) {
        case POOLING_MAX:
            return new CpuMaxPoolingFunction();
        default:
            throw IllegalArgumentException();
    }
}

ResponseNormalizationFunction *CpuPlatform::createResponseNormalizationFunction(LayerType type) {
    switch (type) {
        case NORMALIZATION_LOCALRESPONSE:
            return new CpuResponseNormalizationFunction();
        default:
            throw IllegalArgumentException();
    }
}

FullyConnectedFunction *CpuPlatform::createFullyConnectedFunction() {
    return new CpuFullyConnectedFunction();
}

PlatformInfo &CpuPlatform::getPlatformInfo() {
    return this->platformInfo;
}

PlatformType CpuPlatform::getPlatformType() {
    return PlatformType::CPU;
}

CpuPlatform::CpuPlatform() {
    platformInfo = *(new PlatformInfo("CPU", PlatformType::CPU, "someID", 100, 3333));
}
