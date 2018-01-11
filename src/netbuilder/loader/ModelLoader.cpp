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


LayerConstructionParams ModelLoader::getLayerConstructionParamsByIndex(int index) {
    json currentLayer = getLayerJSON(index);
    LayerConstructionParams lp;
    lp.type = currentLayer["layerType"];
    if (currentLayer.count("filterSize") != 0) {
        lp.filterSize = currentLayer["filterSize"];
    }
    if (currentLayer.count("numFilters") != 0)
        lp.filterSize = currentLayer["kernels"];

    if (currentLayer.count("stride") != 0)
        lp.filterSize = currentLayer["stride"];


    // TODO: all params need to be covered!

    return lp;

}