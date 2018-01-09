cmake_minimum_required(VERSION 3.5)

project(HICS)

set(CMAKE_CXX_STANDARD 11)

# Prepare "Catch" library for other executables
set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/catch)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

find_package(Qt5 COMPONENTS Core Widgets)
find_package(HDF5)

enable_testing()

add_subdirectory(tests)

add_subdirectory(src)
