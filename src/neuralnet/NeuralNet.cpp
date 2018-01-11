//
// Created by Maximilian Franz on 07.01.18.
//

#include "NeuralNet.h"
#include "../NotImplementedException.h"

void NeuralNet::addLayer(Layer *layer) {
    layers.push_back(layer);
}

NetIterator *NeuralNet::createIterator() {

}
