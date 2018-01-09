//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <vector>
#include <list>

class Wrapper {
protected:
    int numDimensions;
    int dimensionSizes;
    // std::vector<float> data;
    // std::list<float> data;
public:

    // pure virtual functions to make Wrapper an abstract class
    virtual int getNumDimensions() = 0;

    virtual int getDimensionSizes() = 0;
};

int Wrapper::getNumDimensions() {
    return numDimensions;
}

int Wrapper::getDimensionSizes() {
    return dimensionSizes;
}
