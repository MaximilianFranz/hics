set(SOURCE_FILES
        PlatformManager.cpp PlatformManager.h
        PlatformInfo.cpp PlatformInfo.h
        platforms/Platform.cpp platforms/Platform.h
        platforms/CpuPlatform.cpp platforms/CpuPlatform.h
        platforms/FpgaPlatform.cpp platforms/FpgaPlatform.h
        layerfunctions/LayerFunction.h
        layerfunctions/CLFunction.cpp layerfunctions/CLFunction.h
        layerfunctions/activation/ActivationFunction.cpp layerfunctions/activation/ActivationFunction.h
        layerfunctions/activation/CpuActivationFunction.cpp layerfunctions/activation/CpuActivationFunction.h
        layerfunctions/convolution/ConvolutionFunction.cpp layerfunctions/convolution/ConvolutionFunction.h
        layerfunctions/convolution/CpuConvolutionFunction.cpp layerfunctions/convolution/CpuConvolutionFunction.h
        layerfunctions/pooling/PoolingFunction.cpp layerfunctions/pooling/PoolingFunction.h
        layerfunctions/pooling/CpuPoolingFunction.cpp layerfunctions/pooling/CpuPoolingFunction.h
        layerfunctions/loss/LossFunction.cpp layerfunctions/loss/LossFunction.h
        layerfunctions/loss/CpuLossFunction.cpp layerfunctions/loss/CpuLossFunction.h)
add_library(platform STATIC ${SOURCE_FILES})
