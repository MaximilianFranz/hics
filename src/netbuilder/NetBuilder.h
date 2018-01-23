//
// Created by David Culley on 07.01.18.
//

#pragma once

#include <vector>
#include <NeuralNet.h>
#include <LayerMaker.h>
#include <map>
#include <vector>
#include "loader/JSONModelLoader.h"

#include "NetInfo.h"

class NetBuilder {

public:

    /***
     * Constructs
     * @param net
     * @return
     */
    NeuralNet* buildNeuralNet(NetInfo net);


    std::vector<NetInfo*> queryAvailableNets();

    std::map<int, std::string> getLabelMap(NetInfo net);

};
