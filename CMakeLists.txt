cmake_minimum_required(VERSION 3.5)

project(HICS VERSION 0.2)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 11)

# switch on various compiler warnings
# https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_GNUC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-reorder -Wall")
endif ()

configure_file(${CMAKE_SOURCE_DIR}/cmake/config.h.cmake ${CMAKE_BINARY_DIR}/config.h)
include_directories(${CMAKE_BINARY_DIR})

include(GNUInstallDirs)
include(ECMInstallIcons)

option(INSTALL "Set this to ON if you plan to install hics system wide via \"make install\"." OFF)

# those defines are expanded to absolute paths
if (INSTALL)
    add_definitions(-DRES_DIR="${CMAKE_INSTALL_SYSCONFDIR}/hics/")
else()
    add_definitions(-DRES_DIR="${CMAKE_SOURCE_DIR}/resources/")
endif()
add_definitions(-DTEST_RES_DIR="${CMAKE_SOURCE_DIR}/tests/resources/")

find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)

# Required by the AlexNetWeightLoader
find_package(HDF5 COMPONENTS C REQUIRED)
include_directories(${HDF5_INCLUDE_DIRS})

# Required by the communicator module
find_package(Protobuf REQUIRED)
find_package(Grpc REQUIRED)

option(PLATFORM_ALTERA "Build project for FPGA platform." OFF)

if(PLATFORM_ALTERA)
    find_package(Altera)
else()
    # Required by the CL platform
    find_package(OpenCL REQUIRED)
endif()

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

option(GUI_COVERAGE "Run Coverage for GUI." OFF)

if (NOT GUI_COVERAGE)
if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    include(CodeCoverage)
    set(COVERAGE_EXCLUDES
            '/usr/*'
            '${CMAKE_SOURCE_DIR}/tests/*'
            '${CMAKE_SOURCE_DIR}/src/gui/handler/*'
            '${CMAKE_SOURCE_DIR}/src/gui/WorkerThread.*'
            '${CMAKE_SOURCE_DIR}/src/communicator/ComputationServer.*'
            '${CMAKE_SOURCE_DIR}/src/communicator/serverMain.cpp'
            '${CMAKE_SOURCE_DIR}/thirdparty/*'
            '${CMAKE_SOURCE_DIR}/catch/*'
            '${CMAKE_SOURCE_DIR}/cmake-build-*'
            '${CMAKE_BINARY_DIR}/*')
    setup_target_for_coverage(NAME test_coverage EXECUTABLE all_tests DEPENDENCIES catchtest)

    APPEND_COVERAGE_COMPILER_FLAGS()
endif() #CMAKE_BUILD_TYPE STREQUAL "Coverage"
else()
if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    include(CodeCoverage)
    set(COVERAGE_EXCLUDES
            '/usr/*'
            '${CMAKE_SOURCE_DIR}/tests/*'
            '${CMAKE_SOURCE_DIR}/src/main.cpp'
            '${CMAKE_SOURCE_DIR}/src/communicator/*'
            '${CMAKE_SOURCE_DIR}/src/exceptions/*'
            '${CMAKE_SOURCE_DIR}/src/executor/*'
            '${CMAKE_SOURCE_DIR}/src/gui/MainWindowSubject.h'
            '${CMAKE_SOURCE_DIR}/src/manager/*'
            '${CMAKE_SOURCE_DIR}/src/netbuilder/*'
            '${CMAKE_SOURCE_DIR}/src/neuralnet/*'
            '${CMAKE_SOURCE_DIR}/src/platform/*'
            '${CMAKE_SOURCE_DIR}/thirdparty/*'
            '${CMAKE_SOURCE_DIR}/catch/*'
            '${CMAKE_SOURCE_DIR}/cmake-build-*'
            '${CMAKE_BINARY_DIR}/*')
    setup_target_for_coverage(NAME test_coverage EXECUTABLE guitestsQt)

    APPEND_COVERAGE_COMPILER_FLAGS()
endif() #CMAKE_BUILD_TYPE STREQUAL "Coverage"
endif()

install(DIRECTORY resources/weights DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}/hics
        FILES_MATCHING PATTERN "*.h5")
install(DIRECTORY resources/models DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}/hics)
install(FILES resources/kernels/gemm3.cl DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}/hics/kernels/)
install(FILES resources/kernels/gemm4_fpga.cl DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}/hics/kernels/)
# Rename those files and install them as examples, as they will need explicit configuration
install(FILES resources/platforms.json DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}/hics/
        RENAME platforms.json.example)
install(FILES resources/computationHosts.json DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}/hics/
        RENAME computationHosts.json.example)

# Install a desktop file for hics, our main GUI
install(FILES data/hics.desktop DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/applications/)
ecm_install_icons(ICONS data/256-apps-hics.png DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/ THEME hicolor)

