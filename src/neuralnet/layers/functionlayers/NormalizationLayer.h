//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <layerfunctions/LayerFunction.h>
#include "layers/Layer.h"

class NormalizationLayer : public Layer {
protected:
    LayerFunction* function;
public:

    std::vector<int> calcOutputDimensions() override;

    virtual void setFunction(LayerFunction* function) = 0;
};

