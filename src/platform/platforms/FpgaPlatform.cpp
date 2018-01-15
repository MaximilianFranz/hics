//
// Created by David Culley on 12.01.18.
//

#include <NotImplementedException.h>
#include "FpgaPlatform.h"

ActivationFunction &FpgaPlatform::createActivationFunction() {
    throw NotImplementedException();
}

ConvolutionFunction &FpgaPlatform::createConvolutionFunction() {
    throw NotImplementedException();
}

LossFunction &FpgaPlatform::createLossFunction() {
    throw NotImplementedException();
}

PoolingFunction &FpgaPlatform::createPoolingFunction() {
    throw NotImplementedException();
}

ResponseNormalizationFunction &FpgaPlatform::createResponseNormalizationFunction() {
    throw NotImplementedException();
}

FullyConnectedFunction &FpgaPlatform::createFullyConnectedFunction() {
    throw NotImplementedException();
}

PlatformInfo &FpgaPlatform::getPlatformInfo() {
    throw NotImplementedException();
}

PlatformType FpgaPlatform::getPlatformType() {
    throw NotImplementedException();
}
