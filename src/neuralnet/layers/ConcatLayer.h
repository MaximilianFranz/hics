//
// Created by Maximilian Franz on 10.01.18.
//

#pragma once

#include "Layer.h"

/**
 * Allows to concatenate multiple outputs from more than one previous layer into one.
 */
class ConcatLayer : Layer {
protected:
    std::vector<Layer> previousLayerList;

};


