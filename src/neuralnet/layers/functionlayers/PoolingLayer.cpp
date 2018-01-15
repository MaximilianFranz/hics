//
// Created by Maximilian Franz on 07.01.18.
//

#include "PoolingLayer.h"
#include "NotImplementedException.h"


std::vector<int> PoolingLayer::calcOutputDimensions() {
    std::vector<int> outDim(3);
    outDim[D3_Z_DIM] = inputDimensions[0]; //number of channels remain the same!
    int outputWidth = (this->inputDimensions[D3_X_DIM] - filterSize) / stride + 1;
    outDim[D3_X_DIM] = outputWidth;
    outDim[D3_Y_DIM] = outputWidth;
    return outDim;
}

void PoolingLayer::forward(DataWrapper &input, DataWrapper &output) {
    this->function->execute(input, output, stride, filterSize, zeroPadding);
}

void PoolingLayer::setFunction(PoolingFunction *function) {
    this->function = function;
    this->functionSet = true;

}
