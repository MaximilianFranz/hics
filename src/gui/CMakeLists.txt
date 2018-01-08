add_executable(gui main.cpp)

target_link_libraries(gui Qt5::Core)

add_library(libgui STATIC  MainWindow.cpp MainWindow.h)