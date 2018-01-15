set(SOURCE_FILES
        PlatformManager.cpp PlatformManager.h
        PlatformInfo.cpp PlatformInfo.h
        platforms/Platform.h
        platforms/CpuPlatform.cpp platforms/CpuPlatform.h
        platforms/FpgaPlatform.cpp platforms/FpgaPlatform.h
        layerfunctions/CLFunction.cpp layerfunctions/CLFunction.h
        layerfunctions/activation/ActivationFunction.h
        layerfunctions/convolution/ConvolutionFunction.h
        layerfunctions/convolution/CpuConvolutionFunction.cpp layerfunctions/convolution/CpuConvolutionFunction.h
        layerfunctions/pooling/PoolingFunction.h
        layerfunctions/loss/LossFunction.h
        layerfunctions/normalization/ResponseNormalizationFunction.cpp layerfunctions/normalization/ResponseNormalizationFunction.h
        layerfunctions/loss/SoftMaxLossFunction.cpp layerfunctions/loss/SoftMaxLossFunction.h
        layerfunctions/activation/ReLUFunction.cpp layerfunctions/activation/ReLUFunction.h
        layerfunctions/pooling/MaxPoolingFunction.cpp layerfunctions/pooling/MaxPoolingFunction.h
        layerfunctions/FullyConnectedFunction.cpp layerfunctions/FullyConnectedFunction.h)
add_library(platform STATIC ${SOURCE_FILES})
