add_subdirectory(communicator)
add_subdirectory(executor)
if(Qt5Core_FOUND AND Qt5Widgets_FOUND)
    add_subdirectory(gui)
endif()
add_subdirectory(manager)
add_subdirectory(netbuilder)
add_subdirectory(neuralnet)
add_subdirectory(platform)

add_executable(hics main.cpp)

target_link_libraries(hics gui executor netbuilder platform manager neuralnet)
