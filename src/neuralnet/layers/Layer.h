//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <wrapper/DataWrapper.h>
#include <LayerInfo.h>
#include <layerfunctions/LayerFunction.h>
#include <wrapper/WeightWrapper.h>

class Layer {
protected:

    LayerInfo info;
    Layer *previous;
    Layer *next;
    LayerFunction function = nullptr; //TODO: changed from design to LayerFunction
    //TODO: changed from design: no input and output Wrappers are held;
    bool computed;
    bool functionSet;

public:
    virtual void forward(DataWrapper &input, DataWrapper &output) = 0;

    virtual LayerInfo getInfo();

    virtual bool isComputed();

    /**
     * TODO: Called from inside forward()?
     *
     * @param status
     * @return
     */
    virtual bool setComputed(bool status);

    virtual bool isLayerFunctionSet();

    virtual void setLayerFunction(LayerFunction &function);

    virtual void reset();

};

