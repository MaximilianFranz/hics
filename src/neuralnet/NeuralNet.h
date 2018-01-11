//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <layers/Layer.h>
#include <NetInfo.h>

#include "NetIterator.h"

class NeuralNet {
private:
    NetInfo info;
    std::vector<Layer*> layers;
    bool computationCompleted;
    bool placementCompleted;
public:
    friend class SimpleNetIterator; // Grants NetIterator access to private members

    void addLayer(Layer* layer);

    NetInfo getInfo() {
        return info;
    }

    bool isComputationComplete() {
        return computationCompleted;
    }

    bool isPlacementComplete() {
        return placementCompleted;
    }

    NetIterator* createIterator();


};

