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

#include <string>
#include <map>

#include <hdf_wrapper.h>

#include "loader/weightloader/WeightLoader.h"

/**
 * @class AlexNetWeightLoader
 *
 * @brief The AlexNetWeightLoader class loads the weights per layer for the AlexNet in a std::map.
 *
 * The AlexNetWeightLoader takes a file path to a AlexNet HDF5-File which contains the weights for it, opens it and
 * loads the weights for every layer in a WeightWrapper. Then the specific WeightWrapper gets mapped to the belonging
 * LayerIdentifier enumerate which is a fixed representation of a layer in a neural net.
 *
 * @author Patrick Deubel
 *
 * @version 1.0
 *
 * @date 11.01.2018
 *
 */

class AlexNetWeightLoader : public WeightLoader {

private:

    const std::string filePath;
    h5cpp::File weightFile;
    std::map<LayerIdentifier, WeightWrapper*> weightsMap;

    /**
     * @brief Creates a WeightWrapper out of a given groupName from the internally stored weightFile.
     *
     * The method tries to access the group by using the groupName string. It will then load the weight and bias dataset
     * out of it and stores the data in one-dimensional std::vector objects. Furthermore it gets the dataset's
     * dimensions and stores everything in a WeightWrapper which will be returned.
     *
     * @param groupName a string representing the group name for which the WeightWrapper shall be created
     * @return the created WeightWrapper
     */
    WeightWrapper* createWeightWrapper(const std::string &groupName);

    WeightWrapper* appendLayers(const std::string &groupNameFirst, const std::string &groupNameSecond);

    void insertWeightWrapper(const LayerIdentifier &layerId, const WeightWrapper *weightWrapper);

    void populateWeightsMap();

public:

    /**
    * @brief Initializes the AlexNetWeightLoader with the given weight file.
    *
    * The constructor will try to load the weights from the given filePath and will then save the weights in the
     * weightsMap. Each Layer will get a WeightWrapper and will be identified with the LayerIdentifier enumerate.
    *
    * @param filePath is the weight file for the AlexNet in HDF5 format
    */
    explicit AlexNetWeightLoader(const std::string &filePath);

    /**
     * @brief Returns the WeightWrapper corresponding to the LayerIdentifier parameter.
     *
     * The method looks up in the weightsMap which WeightWrapper is mapped to the layerId key and returns it.
     *
     * @param layerId is the identification for the wanted WeightWrapper in the weightsMap
     * @return the wanted WeightWrapper
     */
    WeightWrapper* getWeights(LayerIdentifier layerId) override; //TODO Maybe change return type to return by reference
};
