add_executable(netbuildertests WrapperTest.cpp WrapperTest.h)

#Link against netbuilder lib to get access to symbols
#Link against catchtest to use the Catch-main function.
target_link_libraries(netbuildertests catchtest hics netbuilder)

add_test(NAME netbuildertest COMMAND tests)