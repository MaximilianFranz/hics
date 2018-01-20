//
// Created by David Culley on 12.01.18.
//

#pragma once

#include "Platform.h"

class CpuPlatform : public Platform {
public:
    ActivationFunction *createActivationFunction(LayerType type) override;

    ConvolutionFunction *createConvolutionFunction() override;

    LossFunction *createLossFunction(LayerType type) override;

    PoolingFunction *createPoolingFunction(LayerType type) override;

    ResponseNormalizationFunction *createResponseNormalizationFunction(LayerType type) override;

    FullyConnectedFunction *createFullyConnectedFunction() override;

    PlatformInfo &getPlatformInfo() override;

    PlatformType getPlatformType() override;

    CpuPlatform();
};
