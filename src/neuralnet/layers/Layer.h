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

    std::vector<Layer*> previousLayers;
    std::vector<Layer*> nextLayers;
    LayerFunction function;
    bool computed;
    bool functionSet;

public:

    LayerInfo info;

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

    virtual bool readyToCompute();

    virtual bool isLayerFunctionSet();

    virtual void setLayerFunction(LayerFunction &function);

    virtual void reset();

    const std::vector<Layer *> &getPreviousLayers() const;

    const std::vector<Layer *> &getNextLayers() const;


};

