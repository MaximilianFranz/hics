//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include "Wrapper.h"

class WeightWrapper : public Wrapper {
private:
    float bias{};

public:
//    WeightWrapper(int numDimensions, int dimensionSizes, const std::vector &data);

    float getBias() const;

    int getNumDimensions() override;

    int getDimensionSizes() override;
};
