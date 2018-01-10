add_executable(tests WrapperTest.cpp WrapperTest.h)

target_link_libraries(tests catchtest hics netbuilder)

add_test(NAME testname COMMAND tests)