add_executable(communicatortests UtilTest.h UtilTest.cpp ClientServerTest.cpp ClientServerTest.h)

#Link against manager lib to get access to symbols
#Link against catchtest to use the Catch-main function.
target_link_libraries(communicatortests catchtest communicator grpc grpc++)

include_directories(${CMAKE_BINARY_DIR}/src/communicator/)

add_test(NAME communicatortest COMMAND communicatortests)

add_definitions(-DHICS_SERVER="${CMAKE_BINARY_DIR}/tests/communicator/")

add_executable(test-server serverTest.cpp)
target_link_libraries(test-server communicator executor platform neuralnet netbuilder protobuf grpc grpc++ catchtest)
