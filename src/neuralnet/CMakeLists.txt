add_library(neuralnet STATIC
        layers/Layer.cpp
        layers/Layer.h
        NetIterator.h
        SimpleNetIterator.cpp SimpleNetIterator.h
        NeuralNet.cpp NeuralNet.h
        layers/functionlayers/PoolingLayer.cpp layers/functionlayers/PoolingLayer.h
        layers/functionlayers/MaxPoolingLayer.cpp layers/functionlayers/MaxPoolingLayer.h
        layers/functionlayers/ActivationLayer.cpp layers/functionlayers/ActivationLayer.h
        layers/functionlayers/ReLUActivationLayer.cpp layers/functionlayers/ReLUActivationLayer.h
        layers/weightlayers/ConvolutionLayer.cpp layers/weightlayers/ConvolutionLayer.h
        layers/functionlayers/LocalResponseNormLayer.cpp layers/functionlayers/LocalResponseNormLayer.h
        layers/functionlayers/LossLayer.cpp layers/functionlayers/LossLayer.h
        layers/functionlayers/SoftMaxLossLayer.cpp layers/functionlayers/SoftMaxLossLayer.h
        layers/naive/InputLayer.cpp layers/naive/InputLayer.h
        layers/weightlayers/FullyConnectedLayer.cpp layers/weightlayers/FullyConnectedLayer.h
        layers/naive/ConcatLayer.cpp layers/naive/ConcatLayer.h layers/naive/NaiveLayer.cpp layers/naive/NaiveLayer.h)