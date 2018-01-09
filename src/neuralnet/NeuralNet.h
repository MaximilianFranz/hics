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
    bool computationCompleted;
    bool placementCompleted;
public:
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

