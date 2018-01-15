//
// Created by David Culley on 13.01.18.
//

#pragma once

#include <string>

#include <PlatformInfo.h>

#include <layerfunctions/pooling/PoolingFunction.h>
#include <layerfunctions/normalization/ResponseNormalizationFunction.h>
#include <layerfunctions/activation/ActivationFunction.h>
#include <layerfunctions/convolution/ConvolutionFunction.h>
#include <layerfunctions/loss/LossFunction.h>
#include <layerfunctions/FullyConnectedFunction.h>

enum PlatformType {
    CPU,
    FPGA,
    GPU,
};

class Platform {
protected:
    PlatformInfo platformInfo;

public:
    virtual ActivationFunction &createActivationFunction() = 0;
    virtual ConvolutionFunction &createConvolutionFunction() = 0;
    virtual LossFunction &createLossFunction() = 0;
    virtual PoolingFunction &createPoolingFunction() = 0;
    virtual ResponseNormalizationFunction &createResponseNormalizationFunction() = 0;
    virtual FullyConnectedFunction &createFullyConnectedFunction() = 0;

    virtual PlatformInfo &getPlatformInfo() = 0;
    virtual PlatformType getPlatformType() = 0;
};
