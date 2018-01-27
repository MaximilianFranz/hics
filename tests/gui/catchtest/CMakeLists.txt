add_executable(guitestsCatch MainWindowSubjectTest.cpp MainWindowSubjectTest.h)

#Link against catchtest to use the Catch-main function.
target_link_libraries(guitestsCatch catchtest hics gui manager)

add_test(NAME guitestCatch COMMAND guitestsCatch)