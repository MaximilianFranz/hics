#set(CMAKE_AUTOMOC ON)
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
#
#set(SOURCE_FILES handler/ui/StartWidgetTest.cpp handler/ui/StartWidgetTest.h
#        handler/MainWindowHandlerTest.cpp handler/MainWindowHandlerTest.h
#        handler/ui/ResultWidgetTest.cpp handler/ui/ResultWidgetTest.h
#        handler/ui/DetailDialogTest.cpp handler/ui/DetailDialogTest.h
#        WorkerThreadTest.h
#        WorkerThreadTest.cpp)
#add_library(guitestsQt ${SOURCE_FILES})
#
#find_package(Qt5Test)
#
#target_link_libraries(guitestsQt _qttest gui manager util netbuilder executor Qt5Test)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(tempTests handler/ui/StartWidgetTest.cpp handler/ui/StartWidgetTest.h
        handler/MainWindowHandlerTest.cpp handler/MainWindowHandlerTest.h
        handler/ui/ResultWidgetTest.cpp handler/ui/ResultWidgetTest.h
        handler/ui/DetailDialogTest.cpp handler/ui/DetailDialogTest.h
        WorkerThreadTest.cpp
        WorkerThreadTest.h
        main.cpp)

find_package(Qt5Test)

#add_test(NAME guitestQt COMMAND guitestsQt)

target_link_libraries(tempTests gui manager util netbuilder executor Qt5::Test)