//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <string>
#include <wrapper/DataWrapper.h>
#include <wrapper/WeightWrapper.h>


/**
 * Abstract class Layer
 */
class Layer {
protected:

    Layer* previousLayer;
    Layer* nextLayer;
    bool computed;
    bool functionSet;

    std::string type;
    std::vector<int> inputDimensions;
    std::vector<int> outputDimensions;


public:
    /**
     * Dimension positions in the dimension vectors according to convention in 3D
     */
    const int D3_X_DIM = 2;
    const int D3_Y_DIM = 1;
    const int D3_Z_DIM = 0;


    virtual void forward(DataWrapper &input, DataWrapper &output) = 0;

    virtual bool isComputed() = 0;

    virtual bool setComputed(bool status) = 0;

    virtual bool readyToCompute() = 0;

    virtual bool isLayerFunctionSet() = 0;

    virtual void reset() = 0;

    virtual void init() = 0;

    virtual std::vector<int> calcOutputDimensions() = 0;

    virtual std::vector<int> getOutputDimensions() = 0;

    Layer *getPreviousLayer() const;

    Layer *getNextLayer() const;

    const std::string &getType() const;

    const std::vector<int> &getInputDimensions() const;

};

