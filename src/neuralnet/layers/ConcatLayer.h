//
// Created by Maximilian Franz on 10.01.18.
//

#pragma once

#include "Layer.h"
#include "NaiveLayer.h"

/**
 * Allows to concatenate multiple outputs from more than one previous layer into one.
 */
class ConcatLayer : NaiveLayer {
protected:
    //TODO: This needs to implement the previous layer functions differently!
    //    std::vector<Layer*> previousLayerList;
public:
private:
    void forward(DataWrapper &input, DataWrapper &output) override;
};


