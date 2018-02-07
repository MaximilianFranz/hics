
#pragma once

#ifdef __APPLE__

#include <OpenCL/opencl.h>

#else
#include <CL/opencl.h>
#endif

#include "ConvolutionFunction.h"

class FpgaConvolutionFunction : public ConvolutionFunction {
private:
    cl_context context;
    cl_device_id device;
    cl_command_queue queue;
    cl_program program;
    cl_kernel kernel;

public:
    void execute(const DataWrapper &input,
                 DataWrapper &output,
                 const WeightWrapper &weights,
                 int stride,
                 int filterSize,
                 int numFilters,
                 int zeroPadding) override;

    FpgaConvolutionFunction(cl_context c, cl_device_id d);

    ~FpgaConvolutionFunction();

};


