set(TEST_SOURCES MainTest.cpp util/FileHelper.cpp)

add_definitions(-DHICS_SERVER="${CMAKE_BINARY_DIR}/tests/communicator/")

# Create a test library which makes Catch available to all tests by linking
# against it.
add_library(catchtest ${TEST_SOURCES})
target_link_libraries(catchtest Catch platform neuralnet netbuilder executor)

include_directories(util)

add_subdirectory(communicator)
add_subdirectory(executor)
add_subdirectory(gui)
add_subdirectory(manager)
add_subdirectory(netbuilder)
add_subdirectory(neuralnet)
add_subdirectory(platform)

include_directories(${CMAKE_BINARY_DIR}/src/communicator)

if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    file(GLOB_RECURSE all_tests_srcs .
            communicator/UtilTest.cpp
            communicator/ClientServerTest.cpp
            executor/*.cpp
            gui/catchtest/*.cpp
            manager/ClassificationResultTest.cpp
            manager/HostPlacerTest.cpp
            manager/ManagerTest.cpp
            manager/PerformanceCalculatorTest.cpp
            manager/PreProcessorTest.cpp
            manager/ClassificationRequestTest.cpp
            manager/OperationModeTest.cpp
            #manager/SystemTest.cpp
            netbuilder/*.cpp
            neuralnet/*.cpp
            platform/*.cpp)

    add_executable(all_tests ${all_tests_srcs})

    #Link against netbuilder lib to get access to symbols
    #Link against catchtest to use the Catch-main function.
    target_link_libraries(all_tests catchtest executor netbuilder manager communicator gui neuralnet platform)
endif ()