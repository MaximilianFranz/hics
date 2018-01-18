//
// Created by David Culley on 07.01.18.
//

#pragma once

#include <vector>
#include "NetInfo.h"

class NetBuilder {

public:
    void buildNeuralNet(NetInfo net);

    std::vector<NetInfo*> queryAvailableNets(); // TODO change return type
};
