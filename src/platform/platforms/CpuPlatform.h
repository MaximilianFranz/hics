//
// Created by David Culley on 12.01.18.
//

#pragma once

#include "Platform.h"

class CpuPlatform : public Platform {
public:
    ConvolutionFunction &createConvolutionFunction() override;

    LossFunction &createLossFunction() override;

    PoolingFunction &createPoolingFunction() override;

    ResponseNormalizationFunction &createResponseNormalizationFunction() override;

    FullyConnectedFunction &createFullyConnectedFunction() override;

    PlatformInfo &getPlatformInfo() override;

    PlatformType getPlatformType() override;

    ActivationFunction &createActivationFunction() override;
};
