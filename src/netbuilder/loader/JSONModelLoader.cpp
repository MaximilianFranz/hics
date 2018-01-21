//
// Created by Maximilian Franz on 07.01.18.
//

#include "JSONModelLoader.h"


JSONModelLoader::JSONModelLoader(string path) : ModelLoader(path){
    this->init();
}

void JSONModelLoader::init() {
    string jsonString = s.getStringFromFile(this->pathToJSON);
    this->model = json::parse(jsonString);
    this->layers = model["layers"];
}

string JSONModelLoader::getNetWorkName() {
    return ModelLoader::model["name"];
}

string JSONModelLoader::getNetWorkID() {
    return model["identifier"];
}

int JSONModelLoader::getRequiredDimension() {
    return model["requiredDimension"];
}

string JSONModelLoader::getLayerTypeByIndex(int index) {
    return layers[index]["layerType"];
}

/**
 * Creates the LayerConstructionParams struct with the parameters, that are retrieved from a json neural net
 * description file.
 *
 * @param index the index of the layer the LayerConstructionParams struct is to be created for
 * @return the LayerConstructionParams struct which contains all the needed information for layer creation
 */
LayerConstructionParams JSONModelLoader::getLayerConstructionParamsByIndex(int index) {
    json currentLayer = getLayerJSON(index);
    LayerConstructionParams lp;
    lp.type = currentLayer["layerType"];
    if (currentLayer.count("activationFct") != 0)
        lp.actFctType = currentLayer["activationFct"];

    if (currentLayer.count("inputSize") != 0)
        lp.inputSize = currentLayer["inputSize"];

    if (currentLayer.count("inputChannels") != 0)
        lp.inputChannels = currentLayer["inputChannels"];

    if (currentLayer.count("filterSize") != 0)
        lp.filterSize = currentLayer["filterSize"];

    if (currentLayer.count("kernels") != 0)
        lp.numFilters = currentLayer["kernels"];

    if (currentLayer.count("stride") != 0)
        lp.stride = currentLayer["stride"];

    if (currentLayer.count("padding") != 0)
        lp.paddingSize = currentLayer["padding"];

    if (currentLayer.count("outputSize") != 0)
        lp.outputSize = currentLayer["outputSize"];

    if (currentLayer.count("params") != 0)
        lp.normParams = currentLayer["params"];

    return lp;
}

json JSONModelLoader::getLayerJSON(int index) {
    return layers[index];
}
