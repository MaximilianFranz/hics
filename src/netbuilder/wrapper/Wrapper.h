//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <vector>

class Wrapper {
protected:
    int numDimensions;
    int dimensionSizes;
//    std::vector data;
public:
    // must have pure virtual functions

    virtual int getNumDimensions() const {
        return numDimensions;
    }

    virtual int getDimensionSizes() const {
        return dimensionSizes;
    }

};
