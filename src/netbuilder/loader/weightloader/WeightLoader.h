//
// Created by David Culley on 07.01.18.
//

#pragma once

#include "../../wrapper/WeightWrapper.h"

class WeightLoader {
private:

public:
    enum class LayerIdentifier {
        CONV_1,
        CONV_2,
        CONV_3,
        CONV_4,
        CONV_5,
        FULLY_CON_1,
        FULLY_CON_2,
        FULLY_CON_3
    };


    // pure virtual function to make WeightLoader an abstract class
    virtual WeightWrapper * getWeights(LayerIdentifier layerId) = 0;
};
