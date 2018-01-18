add_executable(executortests ExecutorTest.cpp ExecutorTest.h)

#Link against netbuilder lib to get access to symbols
#Link against catchtest to use the Catch-main function.
target_link_libraries(executortests catchtest hics executor netbuilder)

add_test(NAME executortests COMMAND netbuildertests)