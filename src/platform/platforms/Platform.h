//
// Created by David Culley on 13.01.18.
//

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

enum class PlatformType {
    CPU,
    FPGA,
    GPU
};

class Platform {
protected:
    PlatformInfo platformInfo; // TODO cant resolve type PlatformInfo

public:
    virtual ActivationFunction *createActivationFunction(LayerType type) = 0;

    virtual ConvolutionFunction *createConvolutionFunction() = 0;

    virtual LossFunction *createLossFunction(LayerType type) = 0;

    virtual PoolingFunction *createPoolingFunction(LayerType type) = 0;

    virtual ResponseNormalizationFunction *createResponseNormalizationFunction(LayerType type) = 0;

    virtual FullyConnectedFunction *createFullyConnectedFunction() = 0;

    virtual PlatformInfo &getPlatformInfo() = 0; // TODO cant resolve type PlatformInfo

    virtual PlatformType getPlatformType() = 0;
};
