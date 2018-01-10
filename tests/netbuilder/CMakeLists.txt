add_executable(tests WrapperTest.cpp WrapperTest.h)

target_link_libraries(tests libtest libhics libnetbuilder)

add_test(NAME testname COMMAND tests)