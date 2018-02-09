add_library(executor STATIC Executor.cpp Executor.h ComputationHost.h PlatformPlacer.cpp PlatformPlacer.h
        Interpreter.cpp Interpreter.h ImageResult.cpp ImageResult.h)
target_link_libraries(executor netbuilder platform)