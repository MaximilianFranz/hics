set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(guitestsQt handler/ui/StartWidgetTest.cpp handler/ui/StartWidgetTest.h
                handler/MainWindowHandlerTest.cpp handler/MainWindowHandlerTest.h
                handler/ui/ResultWidgetTest.cpp handler/ui/ResultWidgetTest.h
                handler/ui/DetailDialogTest.cpp handler/ui/DetailDialogTest.h
                main.cpp)

find_package(Qt5Test)

add_test(NAME guitestQt COMMAND guitestsQt)

target_link_libraries(guitestsQt gui manager util netbuilder executor Qt5::Test)