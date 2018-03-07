add_executable(managertests PreProcessorTest.cpp PreProcessorTest.h ClassificationResultTest.cpp
        ClassificationResultTest.h HostPlacerTest.cpp HostPlacerTest.h PerformanceCalculatorTest.cpp
        PerformanceCalculatorTest.h ManagerTest.cpp ClassificationRequestTest.cpp ClassificationRequestTest.h OperationModeTest.cpp OperationModeTest.h)

#Link against manager lib to get access to symbols
#Link against catchtest to use the Catch-main function.
target_link_libraries(managertests catchtest manager netbuilder platform executor)

add_test(NAME managertest COMMAND managertests)