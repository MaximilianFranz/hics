set(SOURCE_FILES
        PlatformManager.cpp PlatformManager.h
        PlatformInfo.cpp PlatformInfo.h
        platforms/Platform.h
        platforms/PlatformType.h
        platforms/CpuPlatform.cpp platforms/CpuPlatform.h
        layerfunctions/CLFunction.cpp layerfunctions/CLFunction.h
        layerfunctions/activation/ActivationFunction.h
        layerfunctions/activation/CpuReLUFunction.cpp layerfunctions/activation/CpuReLUFunction.h
        layerfunctions/convolution/ConvolutionFunction.h
        layerfunctions/convolution/CpuConvolutionFunction.cpp layerfunctions/convolution/CpuConvolutionFunction.h
        layerfunctions/pooling/PoolingFunction.h
        layerfunctions/pooling/CpuMaxPoolingFunction.cpp layerfunctions/pooling/CpuMaxPoolingFunction.h
        layerfunctions/loss/LossFunction.h
        layerfunctions/loss/CpuSoftMaxLossFunction.cpp layerfunctions/loss/CpuSoftMaxLossFunction.h
        layerfunctions/normalization/ResponseNormalizationFunction.h
        layerfunctions/normalization/CpuResponseNormalizationFunction.cpp layerfunctions/normalization/CpuResponseNormalizationFunction.h
        layerfunctions/FullyConnectedFunction.h
        layerfunctions/CpuFullyConnectedFunction.h layerfunctions/CpuFullyConnectedFunction.cpp
        util/im2col.cpp util/im2col.h)
add_library(platform STATIC ${SOURCE_FILES})
target_link_libraries(platform netbuilder)

add_executable(platform-exec util/main.cpp)
target_link_libraries(platform-exec platform)
