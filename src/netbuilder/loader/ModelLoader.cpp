//
// Created by Kateryna Prokopenko on 10.01.18.
//

#include "ModelLoader.h"
#include "json.hpp"

ModelLoader::ModelLoader(string path) {
    this->pathToJSON = path;
    this->init();
}

void ModelLoader::init() {
    string jsonString = s.getStringFromFile(this->pathToJSON);
    this->model = json::parse(jsonString);
    this->layers = model["layers"];
}

json ModelLoader::getLayerJSON(int index) {
    return layers[index];
}

string ModelLoader::getNetWorkName() {
    return model["name"];
}

string ModelLoader::getNetWorkID() {
    return model["identifier"];
}

int ModelLoader::getRequiredDimension() {
    return model["requiredDimension"];
}

string ModelLoader::getLayerTypeByIndex(int index) {
    return layers[index]["layerType"];
}
/**
 * Checks if parameter, that must be an integer, exactly is an integer and if its value is valid (greater than 0).
 * @param currentLayer the layer the parameter of what needs to be checked
 * @param param the parameter that needs to be checked
 * @return true if parameter is valid
 */
bool checkIntParam(json currentLayer, string param) {
    bool valid = false;
    if (typeid(currentLayer["inputSize"]).name() == "int"
        && currentLayer["inputSize"] > 0)
        valid = true;
    return valid;
}

/**
 * Creates the LayerConstructionParams struct with the parameters, that are retrieved from a json neural net
 * description file.
 * @param index the index of the layer the LayerConstructionParams struct is to be created for
 * @return the LayerConstructionParams struct which contains all the needed information for layer creation
 */
LayerConstructionParams ModelLoader::getLayerConstructionParamsByIndex(int index) {
    json currentLayer = getLayerJSON(index);
    LayerConstructionParams lp;
    lp.type = currentLayer["layerType"];
    if (currentLayer.count("activationFct") != 0)
        lp.actFctType = currentLayer["activationFct"];

    if (currentLayer.count("inputSize") != 0 && checkIntParam(currentLayer, "inputSize"))
        lp.filterSize = currentLayer["inputSize"];

    if (currentLayer.count("inputChannels") != 0 && checkIntParam(currentLayer, "inputChannels"))
        lp.filterSize = currentLayer["inputChannels"];

    if (currentLayer.count("filterSize") != 0 && checkIntParam(currentLayer, "filterSize"))
        lp.filterSize = currentLayer["filterSize"];

    if (currentLayer.count("numFilters") != 0 && checkIntParam(currentLayer, "numFilters"))
        lp.filterSize = currentLayer["kernels"];

    if (currentLayer.count("stride") != 0 && checkIntParam(currentLayer, "stride"))
        lp.filterSize = currentLayer["stride"];

    if (currentLayer.count("padding") != 0 && checkIntParam(currentLayer, "padding"))
        lp.filterSize = currentLayer["padding"];

    if (currentLayer.count("outputSize") != 0 && checkIntParam(currentLayer, "outputSize"))
        lp.filterSize = currentLayer["outputSize"];

    if (currentLayer.count("params") != 0)
        lp.normParams = currentLayer["params"];

    return lp;

}