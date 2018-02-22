//
// Created by David Culley on 07.01.18.
//

#pragma once

#include <vector>
#include <map>

#include "NeuralNet.h"
#include "NetInfo.h"


class NetBuilder {

public:

    /***
     * Constructs a neural net based on given net information.
     *
     * @param net net information
     * @return a new NeuralNet object created from given NetInfo object
     */
    NeuralNet* buildNeuralNet(NetInfo net);

    /**
     * Provides a list of available net information objects.
     * @return a vector with the pointers to netInfos of neural nets that can be built
     */
    std::vector<NetInfo*> queryAvailableNets();

    /**
     * Provides a list of classes objects on the image can be classified into.
     * @param net net information
     * @return a map with numbers from 1 to 1000 and classes that correspond to them
     */
    std::map<int, std::string> getLabelMap(NetInfo *net);

    //Static path to the model directory.
    const std::string MODEL_DIR = RES_DIR "models";
};
