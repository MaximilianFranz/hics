add_executable(communicatortests UtilTest.h UtilTest.cpp)

#Link against manager lib to get access to symbols
#Link against catchtest to use the Catch-main function.
target_link_libraries(communicatortests catchtest hics communicator)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME communicatortest COMMAND communicatortests)