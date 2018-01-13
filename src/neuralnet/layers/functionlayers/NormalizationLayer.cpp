//
// Created by Maximilian Franz on 07.01.18.
//

#include "NormalizationLayer.h"
#include "NotImplementedException.h"


void NormalizationLayer::setFunction(LayerFunction *function) {
    this->function = function;

}

std::vector<int> NormalizationLayer::calcOutputDimensions() {
    return inputDimensions; //Normalization does not change output dimensions.
}

