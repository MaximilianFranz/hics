//
// Created by David Culley on 12.01.18.
//

#pragma once

#include "Platform.h"

class FpgaPlatform : public Platform {
public:
    ActivationFunction &createActivationFunction() override;

    ConvolutionFunction &createConvolutionFunction() override;

    LossFunction &createLossFunction() override;

    PoolingFunction &createPoolingFunction() override;

    ResponseNormalizationFunction &createResponseNormalizationFunction() override;

    FullyConnectedFunction &createFullyConnectedFunction() override;

    PlatformInfo &getPlatformInfo() override;

    PlatformType getPlatformType() override;
};
