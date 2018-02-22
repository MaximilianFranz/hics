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

#include "AlexNetWeightLoader.h"

WeightWrapper *AlexNetWeightLoader::createWeightWrapper(const std::string &groupName) {

    std::string datasetWeightName = groupName + "_W";
    std::string datasetBiasName = groupName + "_b";

    h5cpp::Group group;
    h5cpp::Dataset dataset;
    h5cpp::Dataspace dataspace;

    int count = 0;
    int maxTries = 2;
    while(true) {
        try {
            //Open the group which will contain the dataset and dataspace
            group = weightFile.root().open_group(groupName);
            //Open the weight dataset and dataspace.
            dataset = group.open_dataset(datasetWeightName);
            dataspace = dataset.get_dataspace();;
            break;
        } catch (std::exception &e) {
            //TODO log error for false group name. Reason: false/corrupted weight file.
            //Reload weights file and try again.
            weightFile = h5cpp::File(filePath, "r");
            if(++count == maxTries) throw e;
        }
    }

    //Save HDF5 dimensions in an array.
    hsize_t weightDimensionArray[H5S_MAX_RANK];
    //Save the dimension rank which represents the real count of dimensions used.
    int weightDimensionCount = dataspace.get_dims(weightDimensionArray);

    //weightDimensions will contain only the used dimensions. HDF5 saves more unused ones.
    std::vector<int> weightDimensions;
    for (int i = 0; i < weightDimensionCount; i++) {
        weightDimensions.push_back((int) weightDimensionArray[i]);
    }
    unsigned long elementCount = dataspace.get_npoints();
    std::vector<float> weightData(elementCount);

    //Read and store the weightData in the float vector.
    dataset.read(&weightData[0]);

    try {
        //Open the bias dataset and dataspace.
        dataset = group.open_dataset(datasetBiasName);
        dataspace = dataset.get_dataspace();
    } catch (std::exception &e){
        //TODO log this error
    }

    hsize_t biasDimensionArray[H5S_MAX_RANK];
    int biasDimensionCount = dataspace.get_dims(biasDimensionArray);

    std::vector<int> biasDimensions;
    for (int i = 0; i < biasDimensionCount; i++) {
        biasDimensions.push_back((int) biasDimensionArray[i]);
    }

    std::vector<float> biasData((unsigned long) dataspace.get_npoints());
    dataset.read(&biasData[0]);

    WeightWrapper *output = new WeightWrapper(weightDimensions, weightData, biasData, biasDimensions);

    return output;
}

WeightWrapper *
AlexNetWeightLoader::appendLayers(const std::string &groupNameFirst, const std::string &groupNameSecond) {

    WeightWrapper *first = createWeightWrapper(groupNameFirst);
    WeightWrapper *second = createWeightWrapper(groupNameSecond);

    std::vector<float> firstWeights = first->getData();
    const std::vector<float> secondWeights = second->getData();

    std::vector<float> firstBias = first->getBias();
    const std::vector<float> secondBias = second->getBias();

    for (auto i : secondWeights) {
        firstWeights.push_back(secondWeights.at((unsigned long) i));
    }

    for (auto i : secondBias) {
        firstBias.push_back(secondBias.at((unsigned long) i));
    }

    //TODO watch out maybe other dimension attributes need to be changed aswell.

    int firstWeightDimension = first->getDimensions().at(0) * 2;

    std::vector<int> temp = first->getDimensions();
    temp.at(0) = firstWeightDimension;

    std::vector<int> temp2;
    temp2.push_back((int) firstBias.size());

    WeightWrapper *output = new WeightWrapper(temp, firstWeights, firstBias, temp2);

    return output;
}

WeightWrapper *AlexNetWeightLoader::getWeights(LayerIdentifier layerId) {

    switch (layerId) {
        case LayerIdentifier::CONV_1 :
            return createWeightWrapper("conv_1");
        case LayerIdentifier::CONV_2 :
            return createWeightWrapper("conv_2");
        case LayerIdentifier::CONV_3 :
            return createWeightWrapper("conv_3");
        case LayerIdentifier::CONV_4 :
            return createWeightWrapper("conv_4");
        case LayerIdentifier::CONV_5 :
            return createWeightWrapper("conv_5");
        case LayerIdentifier::FULLY_CON_1 :
            return createWeightWrapper("dense_1");
        case LayerIdentifier::FULLY_CON_2 :
            return createWeightWrapper("dense_2");
        case LayerIdentifier::FULLY_CON_3 :
            return createWeightWrapper("dense_3");
        default:
            //TODO throw exception here. Could happen when LayerIdentifier gets expanded but is forgotten here.
            return nullptr;
    }
    return nullptr; //DOES NOT HAPPEN
}


AlexNetWeightLoader::AlexNetWeightLoader(const std::string &filePath)
    : filePath(filePath) {
    try {
        weightFile = h5cpp::File(filePath, "r");
    } catch (std::exception &e) {
        //Weight File Error is crucial
        //TODO act accordingly -> log
    }
}