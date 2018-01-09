# Make test executable
set(TEST_SOURCES MainTest.cpp MainTest.h WrapperTest.cpp WrapperTest.h)
add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests Catch libhics)
#
add_test(NAME testname COMMAND tests)