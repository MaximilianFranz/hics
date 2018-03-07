include_directories(${CMAKE_BINARY_DIR}/src/communicator)

add_library(manager STATIC
        Manager.cpp
        Manager.h
        PreProcessor.cpp
        PreProcessor.h
        PerformanceCalculator.cpp
        PerformanceCalculator.h
        HostPlacer.cpp
        HostPlacer.h
        ClassificationRequest.cpp
        ClassificationRequest.h
        ClassificationResult.cpp
        ClassificationResult.h
        PerformanceData.cpp
        PerformanceData.h
        OperationMode.h
        ManagerObserver.h)

target_link_libraries(manager Qt5::Gui Qt5::Core Qt5::Widgets gui executor communicator protobuf grpc grpc++)
