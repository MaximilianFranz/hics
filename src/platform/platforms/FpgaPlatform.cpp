#include <NotImplementedException.h>
#include <IllegalArgumentException.h>

#include <layerfunctions/loss/CpuSoftMaxLossFunction.h>
#include <layerfunctions/normalization/CpuResponseNormalizationFunction.h>
#include <layerfunctions/CpuFullyConnectedFunction.h>
#include <layerfunctions/pooling/CpuMaxPoolingFunction.h>
#include <layerfunctions/activation/CpuReLUFunction.h>
#include <layerfunctions/convolution/FpgaConvolutionFunction.h>

#include "FpgaPlatform.h"


ActivationFunction *FpgaPlatform::createActivationFunction(LayerType type) {
    switch (type) {
        case ACTIVATION_RELU:
            return new CpuReLUFunction();
        default:
            throw IllegalArgumentException();
    }
}

ConvolutionFunction *FpgaPlatform::createConvolutionFunction() {
    return new FpgaConvolutionFunction();
}

LossFunction *FpgaPlatform::createLossFunction(LayerType type) {
    switch (type) {
        case LOSS_SOFTMAX:
            return new CpuSoftMaxLossFunction();
        default:
            throw IllegalArgumentException();
    }
}

PoolingFunction *FpgaPlatform::createPoolingFunction(LayerType type) {
    switch (type) {
        case POOLING_MAX:
            return new CpuMaxPoolingFunction();
        default:
            throw IllegalArgumentException();
    }
}

ResponseNormalizationFunction *FpgaPlatform::createResponseNormalizationFunction(LayerType type) {
    switch (type) {
        case NORMALIZATION_LOCALRESPONSE:
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

PlatformType FpgaPlatform::getPlatformType() {
    return PlatformType::CPU;
}

FpgaPlatform::FpgaPlatform() {}

FpgaPlatform::FpgaPlatform(PlatformInfo &info) : Platform(info) {}
