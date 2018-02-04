add_executable(neuralnettests NeuralNetTest.cpp NeuralNetTest.h)

target_link_libraries(neuralnettests catchtest neuralnet)

add_test(NAME neuralnettest COMMAND neuralnettests)
