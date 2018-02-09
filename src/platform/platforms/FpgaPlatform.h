#pragma once

#ifdef __APPLE__

#include <OpenCL/opencl.h>

#else
#include "CL/opencl.h"
#endif

#include "Platform.h"


class FpgaPlatform : public Platform {
private:
    cl_context context;
    cl_device_id device;
    ConvolutionFunction *c = nullptr;
    void init();

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

    ~FpgaPlatform();
};
