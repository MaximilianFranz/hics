//
// Created by Maximilian Franz on 07.01.18.
//

#include "MaxPoolingLayer.h"
#include "NotImplementedException.h"


MaxPoolingLayer::MaxPoolingLayer(std::vector<int> inputDimensions, int stride, int filterSize, int zeroPadding)
        : PoolingLayer(inputDimensions, stride, filterSize, zeroPadding) {
    this->type = POOLING_MAX;
    this->outputDimensions = calcOutputDimensions();
    init();

}
