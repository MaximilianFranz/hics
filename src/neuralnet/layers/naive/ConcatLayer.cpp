//
// Created by Maximilian Franz on 10.01.18.
//

#include <NotImplementedException.h>
#include "ConcatLayer.h"

//TODO implement concatenation directly here!
void ConcatLayer::forward(DataWrapper &input, DataWrapper &output) {
    throw NotImplementedException();
}

void ConcatLayer::setPreviousLayer(Layer *previousLayer) {
    previousLayerList.push_back(previousLayer);
}

// Default. This however does not make sense it just provides fail safety if requested.
Layer *ConcatLayer::getPreviousLayer() const {
    return previousLayerList.at(0);
}

ConcatLayer::ConcatLayer(std::vector<std::vector<int>> inputLayersDimensions) {
    this->functionSet = true; // Naive layers don't require LayerFunction

}


