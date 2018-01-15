cmake_minimum_required(VERSION 3.5)

project(HICS)

set(CMAKE_CXX_STANDARD 11)

find_package(Qt5 COMPONENTS Core Widgets Gui)
find_package(HDF5 COMPONENTS C)



#this allows us to use direct includes instead of using relative paths
include_directories(src/communicator)
include_directories(src/executor)
include_directories(src/gui)
include_directories(src/manager)
include_directories(src/netbuilder)
include_directories(src/neuralnet)
include_directories(src/platform)
include_directories(src)

add_subdirectory(src)

# Prepare "Catch" library for other executables, so they can link against 'Catch'
set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/catch)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

enable_testing()

add_subdirectory(tests)

