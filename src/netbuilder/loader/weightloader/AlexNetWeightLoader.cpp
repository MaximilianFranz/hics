//
// Created by David Culley on 07.01.18.
//

#include "AlexNetWeightLoader.h"


WeightWrapper
AlexNetWeightLoader::createWeightWrapper(const std::string &groupName) {

    std::string datasetWeightName = groupName + "_W";
    std::string datasetBiasName = groupName + "_b";

    h5cpp::Group group = weightFile.root().open_group(groupName);

    //Open the weight dataset and dataspace.
    h5cpp::Dataset dataset = group.open_dataset(datasetWeightName);
    h5cpp::Dataspace dataspace = dataset.get_dataspace();

    //Save HDF5 dimensions in an array.
    hsize_t weightDimensionArray[H5S_MAX_RANK];
    //Save the dimension rank which represents the real count of dimensions used.
    int weightDimensionCount = dataspace.get_dims(weightDimensionArray);

    //weightDimensions will contain only the used dimensions. HDF5 saves more unused ones.
    std::vector<int> weightDimensions;
    for (int i = 0; i < weightDimensionCount; i++) {
        weightDimensions.push_back((int)weightDimensionArray[i]);
    }

    std::vector<float> weightData((unsigned long)dataspace.get_npoints());

    //Read and store the weightData in the float vector.
    dataset.read(&weightData[0]);

    //Open the bias dataset and dataspace.
    dataset = group.open_dataset(datasetBiasName);
    dataspace = dataset.get_dataspace();

    hsize_t biasDimensionArray[H5S_MAX_RANK];
    int biasDimensionCount = dataspace.get_dims(biasDimensionArray);

    std::vector<int> biasDimensions;
    for (int i = 0; i < biasDimensionCount; i++) {
        biasDimensions.push_back((int)biasDimensionArray[i]);
    }

    std::vector<float> biasData((unsigned long)dataspace.get_npoints());
    dataset.read(&biasData[0]);

    WeightWrapper output(weightDimensions, weightData, biasData, biasDimensions);

    return output;
}

WeightWrapper AlexNetWeightLoader::appendLayers(const std::string &groupNameFirst, const std::string &groupNameSecond) {

    WeightWrapper first = createWeightWrapper(groupNameFirst);
    WeightWrapper second = createWeightWrapper(groupNameSecond);

    std::vector<float> firstWeights = first.getData();
    const std::vector<float> secondWeights = second.getData();

    std::vector<float> firstBias = first.getBias();
    const std::vector<float> secondBias = second.getBias();

    for (auto i : secondWeights){
        firstWeights.push_back(secondWeights.at((unsigned long) i));
    }

    for (auto i : secondBias) {
        firstBias.push_back(secondBias.at((unsigned long) i));
    }

    //TODO watch out maybe other dimension attributes need to be changed aswell.

    int firstWeightDimension = first.getDimensions().at(0) * 2;

    std::vector<int> temp = first.getDimensions();
    temp.at(0) = firstWeightDimension;

    std::vector<int> temp2;
    temp2.push_back((int) firstBias.size());

    WeightWrapper output(temp, firstWeights, firstBias, temp2);

    return output;
}

void AlexNetWeightLoader::insertWeightWrapper(LayerIdentifier layerId, WeightWrapper weightWrapper){
    weightsMap.insert(std::pair<LayerIdentifier, WeightWrapper>(layerId, weightWrapper));
}

void AlexNetWeightLoader::populateWeightsMap() {

    insertWeightWrapper(LayerIdentifier::CONV_1, createWeightWrapper("conv_1"));

    insertWeightWrapper(LayerIdentifier::CONV_2, appendLayers("conv_2_1", "conv_2_2"));

    insertWeightWrapper(LayerIdentifier::CONV_3, createWeightWrapper("conv_3"));

    insertWeightWrapper(LayerIdentifier::CONV_4, appendLayers("conv_4_1", "conv_4_2"));

    insertWeightWrapper(LayerIdentifier::CONV_5, appendLayers("conv_5_1", "conv_5_2"));

    insertWeightWrapper(LayerIdentifier::FULLY_CON_1, createWeightWrapper("dense_1"));

    insertWeightWrapper(LayerIdentifier::FULLY_CON_2, createWeightWrapper("dense_2"));

    insertWeightWrapper(LayerIdentifier::FULLY_CON_3, createWeightWrapper("dense_3"));
}

WeightWrapper AlexNetWeightLoader::getWeights(LayerIdentifier layerId) {
    return weightsMap.at(layerId);
}


AlexNetWeightLoader::AlexNetWeightLoader(const std::string &filePath)
        : filePath(filePath) {
    weightFile = h5cpp::File(filePath, "r");

    populateWeightsMap();

}