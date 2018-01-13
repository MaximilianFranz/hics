//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include "layers/Layer.h"
#include "NaiveLayer.h"

class InputLayer : NaiveLayer {
    void forward(DataWrapper &input, DataWrapper &output) override;
};

