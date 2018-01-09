//
// Created by David Culley on 07.01.18.
//

#pragma once

#include "NetInfo.h"

class NetBuilder {

public:
    void buildNeuralNet(NetInfo net);

    void queryAvailableNets(); // TODO change return type
};
