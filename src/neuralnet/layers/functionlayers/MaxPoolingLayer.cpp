//
// Created by Maximilian Franz on 07.01.18.
//

#include "MaxPoolingLayer.h"
#include "NotImplementedException.h"


MaxPoolingLayer::MaxPoolingLayer(std::vector<int> inputDimensions, int stride, int filterSize, int zeroPadding) {

    this->inputDimensions = inputDimensions;
    this->stride = stride;
    this->filterSize = filterSize;
    this->zeroPadding = zeroPadding;
    this->outputDimensions = calcOutputDimensions(); //Implemented in PoolingLayer.cpp
    type = "maxpooling";
    init();

}
