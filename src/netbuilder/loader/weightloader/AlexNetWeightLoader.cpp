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

#include <hdf_wrapper.h>
#include <ResourceException.h>
#include "AlexNetWeightLoader.h"

WeightWrapper *AlexNetWeightLoader::createWeightWrapper(const std::string &groupName) {

    std::string datasetWeightName = groupName + "_W";
    std::string datasetBiasName = groupName + "_b";

    h5cpp::Group group;
    h5cpp::Dataset dataset;
    h5cpp::Dataspace dataspace;

    while (true) {
        try {
            //Open the group which will contain the dataset and dataspace
            group = weightFile->root().open_group(groupName);
            //Open the weight dataset and dataspace.
            dataset = group.open_dataset(datasetWeightName);
            dataspace = dataset.get_dataspace();;
            break;
        } catch (h5cpp::Exception &e) {
            throw ResourceException("The AlexNet weight file <" + filePath + "> is corrupt or false. Please ask a HICS"
                                    + " developer for the original weight file.");
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

    std::vector<float> weightData;

    try {
        std::vector<float> temp((unsigned long) dataspace.get_npoints());
        weightData = temp;

        //Read and store the weightData in the float vector.
        dataset.read(&weightData[0]);
    } catch (h5cpp::Exception &e) {
        throw ResourceException("The AlexNet weight file <" + filePath + "> is corrupt or false. Please ask a HICS"
                                + " developer for the original weight file.");
    }

    try {
        //Open the bias dataset and dataspace.
        dataset = group.open_dataset(datasetBiasName);
        dataspace = dataset.get_dataspace();
    } catch (h5cpp::Exception &e) {
        throw ResourceException("The AlexNet weight file <" + filePath + "> is corrupt or false. Please ask a HICS"
                                + " developer for the original weight file.");
    }

    hsize_t biasDimensionArray[H5S_MAX_RANK];
    int biasDimensionCount = dataspace.get_dims(biasDimensionArray);

    std::vector<int> biasDimensions;
    for (int i = 0; i < biasDimensionCount; i++) {
        biasDimensions.push_back((int) biasDimensionArray[i]);
    }

    std::vector<float> biasData;
    try {
        std::vector<float> temp((unsigned long) dataspace.get_npoints());
        biasData = temp;
        dataset.read(&biasData[0]);
    } catch (h5cpp::Exception &e) {
        throw ResourceException("The AlexNet weight file <" + filePath + "> is corrupt or false. Please ask a HICS"
                                + " developer for the original weight file.");
    }

    WeightWrapper *output = new WeightWrapper(weightDimensions, weightData, biasData, biasDimensions);

    return output;
}

WeightWrapper *AlexNetWeightLoader::getWeights(LayerIdentifier layerId) {

    if (layerId == LayerIdentifier::CONV_1) {
        return createWeightWrapper("conv_1");
    } else if (layerId == LayerIdentifier::CONV_2) {
        return createWeightWrapper("conv_2");
    } else if (layerId == LayerIdentifier::CONV_3) {
        return createWeightWrapper("conv_3");
    } else if (layerId == LayerIdentifier::CONV_4) {
        return createWeightWrapper("conv_4");
    } else if (layerId == LayerIdentifier::CONV_5) {
        return createWeightWrapper("conv_5");
    } else if (layerId == LayerIdentifier::FULLY_CON_1) {
        return createWeightWrapper("dense_1");
    } else if (layerId == LayerIdentifier::FULLY_CON_2) {
        return createWeightWrapper("dense_2");
    } else {
        assert(layerId == LayerIdentifier::FULLY_CON_3);
        return createWeightWrapper("dense_3");
    }
}

AlexNetWeightLoader::AlexNetWeightLoader(const std::string &filePath)
    : filePath(filePath) {

    //Disable HDF5 error reporting
    h5cpp::disableAutoErrorReporting();
    try {
        weightFile =  new h5cpp::File(filePath, "r");
    } catch (h5cpp::Exception &e) {
        //Weight File cannot be accessed/read from
        throw ResourceException("The AlexNet weights file <" + filePath + "> is not readable.");
    }
}

AlexNetWeightLoader::~AlexNetWeightLoader() {
    delete weightFile;
}
