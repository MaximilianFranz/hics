set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(guitestsQt handler/ui/StartWidgetTest.cpp handler/ui/StartWidgetTest.h)

find_package(Qt5Test REQUIRED)

add_test(NAME guitestQt COMMAND guitestsQt)

target_link_libraries(guitestsQt hics gui manager util netbuilder executor Qt5::Test)