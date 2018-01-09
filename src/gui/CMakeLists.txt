# Execute Qt macro and .ui files
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(gui main.cpp)

set(SOURCE_FILES
    main.cpp
    MainWindow.cpp
    MainWindow.h
    MainWindow.ui
    StartWidget.cpp
    StartWidget.h
    StartWidget.ui
    ResultWidget.cpp
    ResultWidget.h
    ResultWidget.ui
    DetailDialog.cpp
    DetailDialog.h
    DetailDialog.ui
    MainWindowSubject.cpp
    MainWindowSubject.h
    MainWindowHandler.cpp
    MainWindowHandler.h
    StartWidgetHandler.cpp
    StartWidgetHandler.h
    ResultWidgetHandler.cpp
    ResultWidgetHandler.h
    DetailDialogHandler.cpp
    DetailDialogHandler.h)

add_library(libgui STATIC ${SOURCE_FILES})

target_link_libraries(libgui Qt5::Core Qt5::Gui Qt5::Widgets)
target_link_libraries(gui libgui)
