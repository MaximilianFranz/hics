//
// Created by David Culley on 07.01.18.
//

#pragma once

#include <vector>
#include <NeuralNet.h>
#include <map>
#include "NetInfo.h"
#include <vector>

class NetBuilder {

public:
    NeuralNet* buildNeuralNet(NetInfo net);


    std::vector<NetInfo*> queryAvailableNets(); // TODO change return type

    std::map<int, std::string> getLabelMap(NetInfo net);

};
