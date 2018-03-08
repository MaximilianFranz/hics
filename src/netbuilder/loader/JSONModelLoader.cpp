/* Copyright 2018 The HICS Authors
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall
 * be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 */

#include <fstream>
#include <ResourceException.h>

#include "JSONModelLoader.h"


JSONModelLoader::JSONModelLoader(std::string path) : ModelLoader(path){
    this->init();
}

void JSONModelLoader::init() {
    try {
        std::ifstream i(this->pathToJSON);
        i >> this->model;
        this->layers = model["layers"];
    } catch (...) { // LCOV_EXCL_LINE
        throw ResourceException("Model JSON could not be read, file corrupted"); // LCOV_EXCL_LINE
    }
}

std::string JSONModelLoader::getNetWorkName() {
    return ModelLoader::model["name"];
}

std::string JSONModelLoader::getNetWorkID() {
    return model["identifier"];
}

int JSONModelLoader::getRequiredDimension() {
    return model["requiredDimension"][1];
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

    if (currentLayer.count("numGroups") != 0)
        lp.numGroups = currentLayer["numGroups"];

    return lp;
}

json JSONModelLoader::getLayerJSON(int index) {
    return layers[index];
}

bool JSONModelLoader::isValid() {
    if (model.count("name") == 0) {
        return false;
    }
    else if (model.count("identifier") == 0) {
        return false;
    }
    else if (model.count("requiredDimension") == 0) {
        return false;
    }
    else return model.count("layers") != 0;
}
