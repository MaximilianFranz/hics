//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <layerfunctions/LayerFunction.h>
#include "layers/Layer.h"

class ActivationLayer : public Layer {
protected:
    LayerFunction* function;
public:
    // TODO: This is not technically correct, because ActivationsLayer should not be instantiated.
    ActivationLayer(std::vector<int> &inputDimensions);

    void forward(DataWrapper &input, DataWrapper &output) override;

    std::vector<int> calcOutputDimensions() override;

    void setFunction(LayerFunction* function);
};


