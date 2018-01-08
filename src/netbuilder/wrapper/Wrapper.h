//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <vector>

class Wrapper {
protected:
    int numDimensions;
    int dimensionSizes;
//    std::vector data{};
public:
    // must have pure virtual functions
//    Wrapper(int numDimensions, int dimensionSizes, const std::vector &data)
//            : data(data), dimensionSizes(dimensionSizes), numDimensions(numDimensions) {}

    virtual int getNumDimensions() const {
        return numDimensions;
    }

    virtual int getDimensionSizes() const {
        return dimensionSizes;
    }

//    virtual const std::vector &getData() const {
//        return data;
//    }
};
