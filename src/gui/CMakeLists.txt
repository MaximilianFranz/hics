add_executable(gui main.cpp)

add_library(libgui STATIC main.cpp MainWindow.cpp MainWindow.h MainWindow.ui)

target_link_libraries(libgui Qt5::Core Qt5::Gui Qt5::Widgets)
