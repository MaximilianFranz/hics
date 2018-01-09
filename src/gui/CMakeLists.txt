# Execute Qt macro and .ui files
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(gui main.cpp)

set(SOURCE_FILES
    main.cpp
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
    MainWindowSubject.cpp
    MainWindowSubject.h
        handler/MainWindowHandler.cpp
        handler/MainWindowHandler.h
        handler/StartWidgetHandler.cpp
        handler/StartWidgetHandler.h
        handler/ResultWidgetHandler.cpp
        handler/ResultWidgetHandler.h
        handler/DetailDialogHandler.cpp
        handler/DetailDialogHandler.h)

add_library(libgui STATIC ${SOURCE_FILES})

target_link_libraries(libgui Qt5::Core Qt5::Gui Qt5::Widgets)
target_link_libraries(gui libgui)