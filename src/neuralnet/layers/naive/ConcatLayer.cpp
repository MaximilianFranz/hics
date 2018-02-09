//
// Created by Maximilian Franz on 10.01.18.
//

#include <NotImplementedException.h>
#include "ConcatLayer.h"


void ConcatLayer::setPreviousLayer(Layer *previousLayer) {
    previousLayerList.push_back(previousLayer);
}

// Default. This however does not make sense it just provides fail safety if requested.
Layer *ConcatLayer::getPreviousLayer() const {
    return previousLayerList.at(0);
}

ConcatLayer::ConcatLayer(std::vector<std::vector<int>> inputLayersDimensions)
{
    this->inputLayersDimensions = inputLayersDimensions;
    this->functionSet = true; // Naive layers don't require LayerFunction
    this->type = CONCAT;
    this->outputDimensions = calcOutputDimensions();


}

// This concatenates multiple layer dimensions by putting them "behind" each other in z dimension
std::vector<int> ConcatLayer::calcOutputDimensions() {
    std::vector<int> outDim(3,0);
    for(Layer* l : previousLayerList) {
        outDim[D3_Z_DIM] += l->getOutputDimensions().at(D3_Z_DIM);
    }
    outDim[D3_Y_DIM] = getPreviousLayer()->getOutputDimensions().at(D3_Y_DIM);
    outDim[D3_X_DIM] = getPreviousLayer()->getOutputDimensions().at(D3_Y_DIM);
    return outDim;
}

//TODO: Implement by iterating over previousLayerList an concatenating outputs.
void ConcatLayer::forward() {
    throw NotImplementedException();

}


