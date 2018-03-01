set(TEST_SOURCES MainTest.cpp util/FileHelper.cpp)

file(GLOB_RECURSE testsrcs .
        communicator/UtilTest.cpp
        executor/*.cpp
        gui/catchtest/*.cpp
        manager/*.cpp
        netbuilder/*.cpp
        neuralnet/*.cpp
        platform/*.cpp)

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

add_executable(all_tests ${testsrcs})

#Link against netbuilder lib to get access to symbols
#Link against catchtest to use the Catch-main function.
target_link_libraries(all_tests catchtest executor netbuilder manager communicator gui neuralnet platform)
