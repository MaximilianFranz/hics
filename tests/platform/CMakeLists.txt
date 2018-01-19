add_executable(platformtests PlatformTest.cpp PlatformTest.h)

target_link_libraries(platformtests catchtest hics platform netbuilder)

add_test(NAME platformtest COMMAND platformtests)
