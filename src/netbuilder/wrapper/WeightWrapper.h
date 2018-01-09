//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include "Wrapper.h"

class WeightWrapper : public Wrapper {
private:
    float bias{};

public:
    float getBias() const;

    int getNumDimensions() override;

    int getDimensionSizes() override;
};
