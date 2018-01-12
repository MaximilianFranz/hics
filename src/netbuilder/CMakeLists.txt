set(SOURCE_FILES
        NetBuilder.cpp
        NetBuilder.h
        NetInfo.cpp
        NetInfo.h
        LayerMaker.cpp
        LayerMaker.h
        wrapper/Wrapper.cpp
        wrapper/Wrapper.h
        wrapper/WeightWrapper.cpp
        wrapper/WeightWrapper.h
        wrapper/ImageWrapper.cpp
        wrapper/ImageWrapper.h
        wrapper/DataWrapper.cpp
        wrapper/DataWrapper.h
        loader/ModelLoader.cpp
        loader/ModelLoader.h
        loader/JSONModelLoader.cpp
        loader/JSONModelLoader.h
        loader/weightloader/WeightLoader.cpp
        loader/weightloader/WeightLoader.h
        loader/weightloader/AlexNetWeightLoader.cpp
        loader/weightloader/AlexNetWeightLoader.h
        loader/weightloader/hdf_wrapper.h
        loader/StringLoader.cpp
        loader/StringLoader.h)

add_library(netbuilder STATIC ${SOURCE_FILES})

add_executable(netbuilder-exec main.cpp)
target_link_libraries( netbuilder-exec ${HDF5_CXX_LIBRARIES} )

target_link_libraries(netbuilder-exec netbuilder)