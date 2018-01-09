cmake_minimum_required(VERSION 3.5)

project(HICS)

set(CMAKE_CXX_STANDARD 11)

# Execute Qt macro and .ui files
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Prepare "Catch" library for other executables
set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/catch)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

find_package(Qt5 COMPONENTS REQUIRED Core Widgets Gui)
find_package(HDF5)

enable_testing()

add_subdirectory(tests)

add_subdirectory(src)
