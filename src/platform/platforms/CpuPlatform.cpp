//
// Created by David Culley on 12.01.18.
//

#include <NotImplementedException.h>
#include <IllegalArgumentException.h>

#include <layerfunctions/activation/CpuReLUFunction.h>
#include <layerfunctions/convolution/CpuConvolutionFunction.h>

#include "CpuPlatform.h"


ActivationFunction* CpuPlatform::createActivationFunction(LayerType type) {
    if (type == LayerType::ACTIVATION_RELU) {
        return new CpuReLUFunction();
    } else {
        throw IllegalArgumentException();
    }
}

ConvolutionFunction* CpuPlatform::createConvolutionFunction() {
    return new CpuConvolutionFunction();
}

LossFunction* CpuPlatform::createLossFunction(LayerType type) {
    throw NotImplementedException();
}

PoolingFunction* CpuPlatform::createPoolingFunction(LayerType type) {
    throw NotImplementedException();
}

ResponseNormalizationFunction* CpuPlatform::createResponseNormalizationFunction(LayerType type) {
    throw NotImplementedException();
}

FullyConnectedFunction* CpuPlatform::createFullyConnectedFunction() {
    throw NotImplementedException();
}

PlatformInfo &CpuPlatform::getPlatformInfo() {
    throw NotImplementedException();
}

PlatformType CpuPlatform::getPlatformType() {
    return PlatformType::CPU;
}
