add_executable(platformtests PlatformTest.cpp PlatformTest.h
        util/im2colTest.cpp util/im2colTest.h)

target_link_libraries(platformtests catchtest hics platform netbuilder)

add_test(NAME platformtest COMMAND platformtests)
