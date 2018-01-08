add_executable(gui main.cpp)

target_link_libraries(gui Qt5::Core)

add_library(libgui STATICgit  MainWindow.cpp MainWindow.h)