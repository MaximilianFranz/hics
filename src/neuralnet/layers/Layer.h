//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <wrapper/DataWrapper.h>
#include <LayerInfo.h>
#include <LayerFunction.h>
#include <wrapper/WeightWrapper.h>

class Layer {
private:
    LayerInfo info;
    //Layer previous;
    //Layer next;
    LayerFunction function; //TODO: changed from design
    WeightWrapper weights;
    //TODO: changed from design: no input and output Wrappers are held;
    bool computed;

public:
    virtual void forward(DataWrapper input, DataWrapper output) = 0;

    virtual LayerInfo getInfo();

    virtual bool isComputed();

    virtual bool isPlatformSet() = 0;

    virtual bool isBiased() = 0; //TODO: Do we need this?

};

