# Make test executable
set(TEST_SOURCES MainTest.cpp WrapperTest.cpp)
add_executable(tests ${TEST_SOURCES})

target_link_libraries(tests Catch libhics libnetbuilder)

add_test(NAME testname COMMAND tests)