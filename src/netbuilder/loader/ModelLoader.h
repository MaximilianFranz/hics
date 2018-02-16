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

#pragma once

// INCLUDES
#include <string>
#include <vector>

#include <json.hpp>

#include "StringLoader.h"


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
    int numGroups = 1;
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
