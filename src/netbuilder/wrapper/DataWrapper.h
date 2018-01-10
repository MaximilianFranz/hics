//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include "Wrapper.h"

class DataWrapper : public Wrapper {
private:
public:


    /**
     * Construct DataWrapper by passing already existing data.
     *
     * @param numDimensions
     * @param DimensionSizes
     * @param data
     */
    DataWrapper(int numDimensions, std::vector<int> dimensionSizes, std::vector<float> &data)
            : Wrapper(numDimensions, dimensionSizes, data){

    }

//    DataWrapper(int numDimensions, int dimensionSizes, const std::vector &data) : Wrapper(numDimensions, dimensionSizes,
//                                                                                          data) {}
};
