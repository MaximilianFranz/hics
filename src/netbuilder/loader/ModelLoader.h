//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include "../../NotImplementedException.h"

#ifndef JSONLOADER_MODELLOADER_H
#define JSONLOADER_MODELLOADER_H

// INCLUDES
#include <string>
#include <vector>

#include "StringLoader.h"
#include "json.hpp"


using json = nlohmann::json;

//INCLUDES END

using namespace std;


/**
 * Contains attributes for all layers, so that the information for every layer could be fed into here.
 * Since the NetBuilder "knows" the type of Layer anyways, it will only access the fields it requires.
 */
struct LayerConstructionParams {
    string type;
    int inputSize = 0;
    int outputSize = 0;
    int inputChannels= 0;
    int filterSize = 0;
    int numFilters = 0;
    int stride = 0;
    int paddingSize = 0;
    string actFctType = "none"; // eg. relu, tanh, sigmoid, ...
    string normFctType = "none";
    nlohmann::basic_json<> normParams = {{"radius", 0}, {"alpha", 0}, {"beta", 0}, {"bias", 0}};
};

class ModelLoader {
protected:
    string pathToJSON;
    json model;
    json layers;
    StringLoader s;


public:
    /**
     * Constructor
     * @param path
     */
     ModelLoader(string path);

    //Methods for NetInfo construction
    virtual string getNetWorkName() = 0;

    virtual string getNetWorkID() = 0;

    virtual int getRequiredDimension() = 0;

    virtual string getLayerTypeByIndex(int index) = 0;

    /**
     * Returns Construction information of a layer
     *
     * @param index of the layer requested
     * @return LayerConstructionParams struct with needed information
     */

    virtual LayerConstructionParams getLayerConstructionParamsByIndex(int index) = 0;
};

#endif //JSONLOADER_MODELLOADER_H

