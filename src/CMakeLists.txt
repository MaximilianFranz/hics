add_subdirectory(communicator)
add_subdirectory(executor)
add_subdirectory(gui)
add_subdirectory(manager)
add_subdirectory(netbuilder)
add_subdirectory(neuralnet)
add_subdirectory(platform)
add_subdirectory(util)

add_executable(hics main.cpp)

target_link_libraries(hics gui executor netbuilder platform manager neuralnet)