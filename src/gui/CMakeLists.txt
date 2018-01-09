# Execute Qt macro and .ui files
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(gui main.cpp)

add_library(libgui STATIC main.cpp MainWindow.cpp MainWindow.h MainWindow.ui)

target_link_libraries(libgui Qt5::Core Qt5::Gui Qt5::Widgets)
target_link_libraries(gui libgui)
