set(TEST_SOURCES MainTest.cpp)

# Create a test library which makes Catch available to all tests by linking
# against it.
add_library(catchtest ${TEST_SOURCES})
target_link_libraries(catchtest Catch)

add_subdirectory(communicator)
add_subdirectory(executor)
add_subdirectory(gui)
add_subdirectory(manager)
add_subdirectory(netbuilder)
add_subdirectory(neuralnet)
add_subdirectory(platform)