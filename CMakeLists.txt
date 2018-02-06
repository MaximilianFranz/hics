cmake_minimum_required(VERSION 3.5)

project(HICS)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 11)

# switch on various compiler warnings
# https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_GNUC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif ()

# those defines are expanded to absolute paths
add_definitions(-DRES_DIR="${CMAKE_SOURCE_DIR}/resources/")
add_definitions(-DTEST_RES_DIR="${CMAKE_SOURCE_DIR}/tests/resources/")

find_package(Qt5 COMPONENTS Core Widgets Gui)

# Required by the AlexNetWeightLoader
find_package(HDF5 COMPONENTS C REQUIRED)
include_directories(${HDF5_INCLUDE_DIRS})

# Required by the communicator module
find_package(Protobuf REQUIRED)
find_package(Grpc REQUIRED)

# This allows us to use direct includes instead of using relative paths
include_directories(src/communicator)
include_directories(src/exceptions)
include_directories(src/executor)
include_directories(src/gui)
include_directories(src/manager)
include_directories(src/netbuilder)
include_directories(src/neuralnet)
include_directories(src/platform)
include_directories(src)
include_directories(thirdparty)

add_subdirectory(src)

# Prepare "Catch" library for other executables, so they can link against 'Catch'
set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/catch)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

enable_testing()

add_subdirectory(tests)

