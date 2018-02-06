#pragma once

#include "Platform.h"

class FpgaPlatform : public Platform {
public:
    ActivationFunction *createActivationFunction(LayerType type) override;

    ConvolutionFunction *createConvolutionFunction() override;

    LossFunction *createLossFunction(LayerType type) override;

    PoolingFunction *createPoolingFunction(LayerType type) override;

    ResponseNormalizationFunction *createResponseNormalizationFunction(LayerType type) override;

    FullyConnectedFunction *createFullyConnectedFunction() override;

    PlatformInfo &getPlatformInfo() override;

    PlatformType getPlatformType() override;

    FpgaPlatform();

    FpgaPlatform(PlatformInfo &info);
};
