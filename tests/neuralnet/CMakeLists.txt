add_executable(neuralnettests NeuralNetTest.cpp NeuralNetTest.h)

target_link_libraries(neuralnettests catchtest hics neuralnet)

add_test(NAME neuralnettest COMMAND tests)