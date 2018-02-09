//
// Created by Maximilian Franz on 10.01.18.
//

#pragma once

#include "layers/Layer.h"
#include "NaiveLayer.h"

/**
 * Allows to concatenate multiple outputs from more than one previous layer into one.
 */
class ConcatLayer : public NaiveLayer {
protected:
    //TODO: This needs to implement the previous layer functions differently!
    std::vector<std::vector<int>> inputLayersDimensions;
    std::vector<Layer*> previousLayerList;
public:

    /**
     * Constructor for a ConcatLayer given the dimensions of all input layers.
     *
     * @param inputLayersDimensions dimensions of all layers that are concatenated by this layer.
     */
    ConcatLayer(std::vector<std::vector<int>> inputLayersDimensions);

    std::vector<int> calcOutputDimensions() override;

    void forward() override;

    void setPreviousLayer(Layer *previousLayer) override;

    Layer *getPreviousLayer() const override;

};


