add_executable(guitests MainWindowSubjectTest.cpp MainWindowSubjectTest.h)

#Link against catchtest to use the Catch-main function.
target_link_libraries(guitests catchtest hics gui manager)

add_test(NAME guitest COMMAND guitests)