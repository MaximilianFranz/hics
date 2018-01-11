//
// Created by Maximilian Franz on 07.01.18.
//

#include "PoolingLayer.h"
#include "../../NotImplementedException.h"

void PoolingLayer::forward(DataWrapper &input, DataWrapper &output) {
    this->function.execute(); //TODO: Pass input and output Wrappers, when signature is updated.
}

