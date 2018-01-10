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
     * @param dimensions
     * @param data
     */
    DataWrapper(std::vector<int> dimensions, std::vector<float> &data);

};
