//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <string>
#include <wrapper/DataWrapper.h>
#include <LayerFunction.h>
#include <wrapper/WeightWrapper.h>


/**
 * Abstract class Layer
 */
class Layer {
protected:

    Layer* previousLayer;
    Layer* nextLayer;
    LayerFunction* function;
    bool computed;
    bool functionSet;

    std::string type;
    std::vector<int> inputDimensions;
    std::vector<int> outputDimensions;


public:

    virtual void forward(DataWrapper &input, DataWrapper &output) = 0;

    virtual bool isComputed() = 0;

    virtual bool setComputed(bool status) = 0;

    virtual bool readyToCompute() = 0;

    virtual bool isLayerFunctionSet() = 0;

    virtual void setLayerFunction(LayerFunction &function) = 0;

    virtual void reset() = 0;


};

