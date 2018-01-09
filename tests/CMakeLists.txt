# Make test executable
set(TEST_SOURCES MainTest.cpp WrapperTest.cpp)
add_executable(tests ${TEST_SOURCES})
#TODO: @Michael wie können wir die Klassen aus hics verwenden?
include_directories(../src)

#TODO: @Michael hier brauche ich libhics, oder nicht?
target_link_libraries(tests Catch libhics libnetbuilder)
#
add_test(NAME testname COMMAND tests)