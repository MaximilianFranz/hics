add_executable(communicatortests UtilTest.h UtilTest.cpp)

#Link against manager lib to get access to symbols
#Link against catchtest to use the Catch-main function.
target_link_libraries(communicatortests catchtest communicator)

include_directories(${CMAKE_BINARY_DIR}/src/communicator)

add_test(NAME communicatortest COMMAND communicatortests)

add_executable(client-exec clientMain.cpp)
target_link_libraries(client-exec communicator executor platform neuralnet netbuilder protobuf grpc grpc++ catchtest)
