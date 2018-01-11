//
// Created by Maximilian Franz on 07.01.18.
//

#include "Layer.h"
#include "../../NotImplementedException.h"

LayerInfo Layer::getInfo() {
    return info;
}

bool Layer::isComputed() {
    return computed;
}

bool Layer::setComputed(bool status) {
    computed = status;
}

bool Layer::isLayerFunctionSet() {
    return functionSet;
}

void Layer::setLayerFunction(LayerFunction &function) {
    this->function = function;
    functionSet = true;
}

void Layer::reset() {
    this->functionSet = false;
    this->computed = false;

}


bool Layer::readyToCompute() {
    for (auto layer : previousLayers) {
        if (!layer->isComputed())
            return false;
    }
    return true;
}

const std::vector<Layer *> &Layer::getPreviousLayers() const {
    return previousLayers;
}

const std::vector<Layer *> &Layer::getNextLayers() const {
    return nextLayers;
}






