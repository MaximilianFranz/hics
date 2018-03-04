set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCE_FILES handler/ui/StartWidgetTest.cpp handler/ui/StartWidgetTest.h
        handler/MainWindowHandlerTest.cpp handler/MainWindowHandlerTest.h
        handler/ui/ResultWidgetTest.cpp handler/ui/ResultWidgetTest.h
        handler/ui/DetailDialogTest.cpp handler/ui/DetailDialogTest.h)
add_library(guitestsQt ${SOURCE_FILES})

find_package(Qt5Test)

target_link_libraries(guitestsQt _qttest gui manager util netbuilder executor Qt5Test)