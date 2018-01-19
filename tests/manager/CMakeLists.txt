add_executable(managertests PreProcessorTest.cpp PreProcessorTest.h ClassificationResultTest.cpp ClassificationResultTest.h)

#Link against manager lib to get access to symbols
#Link against catchtest to use the Catch-main function.
target_link_libraries(managertests catchtest hics manager netbuilder)

add_test(NAME managertest COMMAND managertests)