//
// Created by Maximilian Franz on 07.01.18.
//

#include "PoolingLayer.h"


std::vector<int> PoolingLayer::calcOutputDimensions() {
    std::vector<int> outDim(3);
    outDim[D3_Z_DIM] = inputDimensions[0]; //number of channels remain the same!
    int outputWidth = (this->inputDimensions[D3_X_DIM] - filterSize) / stride + 1;
    outDim[D3_X_DIM] = outputWidth;
    outDim[D3_Y_DIM] = outputWidth;
    return outDim;
}

void PoolingLayer::setFunction(PoolingFunction *function) {
    this->function = function;
    this->functionSet = true;

}


void PoolingLayer::forward() {
    outputWrapper = new DataWrapper(getOutputDimensions());
    this->function->execute(*previousLayer->getOutputWrapper(), *outputWrapper, stride, filterSize, zeroPadding);
    computed = true;
}

int PoolingLayer::getFilterSize() const {
    return filterSize;
}

int PoolingLayer::getZeroPadding() const {
    return zeroPadding;
}

int PoolingLayer::getStride() const {
    return stride;
}
