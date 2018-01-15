//
// Created by David Culley on 12.01.18.
//

#include <NotImplementedException.h>
#include "CpuPlatform.h"

ActivationFunction &CpuPlatform::createActivationFunction() {
    throw NotImplementedException();
}

ConvolutionFunction &CpuPlatform::createConvolutionFunction() {
    throw NotImplementedException();
}

LossFunction &CpuPlatform::createLossFunction() {
    throw NotImplementedException();
}

PoolingFunction &CpuPlatform::createPoolingFunction() {
    throw NotImplementedException();
}

ResponseNormalizationFunction &CpuPlatform::createResponseNormalizationFunction() {
    throw NotImplementedException();
}

FullyConnectedFunction &CpuPlatform::createFullyConnectedFunction() {
    throw NotImplementedException();
}

PlatformInfo &CpuPlatform::getPlatformInfo() {
    throw NotImplementedException();
}

PlatformType CpuPlatform::getPlatformType() {
    throw NotImplementedException();
}
