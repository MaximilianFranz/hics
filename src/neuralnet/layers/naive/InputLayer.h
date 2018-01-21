//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include "layers/Layer.h"
#include "NaiveLayer.h"

/**
 * Is the first layer in a network and takes it's inputs.
 *
 * This layer must explicitly set it's inputWrapper, because there is no previous layer!
 */
class InputLayer : public NaiveLayer {
public:
    /**
     * Constructor for an InputLayer
     *
     * This layer must explicitly set it's inputWrapper, because there is no previous layer!
     *
     * @param inputDimensions
     */
    InputLayer(std::vector<int> inputDimensions);


    std::vector<int> calcOutputDimensions() override;

    void forward() override;
};

