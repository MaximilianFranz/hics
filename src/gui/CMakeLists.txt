# Execute Qt macro and .ui files
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCE_FILES
        handler/ui/MainWindow.cpp
        handler/ui/MainWindow.h
        handler/ui/MainWindow.ui
        handler/ui/StartWidget.cpp
        handler/ui/StartWidget.h
        handler/ui/StartWidget.ui
        handler/ui/ResultWidget.cpp
        handler/ui/ResultWidget.h
        handler/ui/ResultWidget.ui
        handler/ui/DetailDialog.cpp
        handler/ui/DetailDialog.h
        handler/ui/DetailDialog.ui
    MainWindowSubject.h
        handler/MainWindowHandler.cpp
        handler/MainWindowHandler.h
        handler/ResultWidgetHandler.cpp
        handler/ResultWidgetHandler.h
        handler/DetailDialogHandler.cpp
        handler/DetailDialogHandler.h)

add_library(gui STATIC ${SOURCE_FILES})
target_link_libraries(gui Qt5::Core Qt5::Gui Qt5::Widgets)

add_executable(gui-exec main.cpp)
target_link_libraries(gui-exec gui netbuilder platform)
