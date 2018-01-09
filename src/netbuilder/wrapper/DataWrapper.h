//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include "Wrapper.h"

class DataWrapper : public Wrapper {
private:
public:
    int getNumDimensions() override;

    int getDimensionSizes() override;

    DataWrapper();

//    DataWrapper(int numDimensions, int dimensionSizes, const std::vector &data) : Wrapper(numDimensions, dimensionSizes,
//                                                                                          data) {}
};
