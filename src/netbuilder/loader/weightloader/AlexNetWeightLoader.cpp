//
// Created by David Culley on 07.01.18.
//

#include "AlexNetWeightLoader.h"


WeightWrapper AlexNetWeightLoader::createWeightWrapper(const std::string &groupName){
    std::string datasetWeightName = groupName + "_W";
    std::string datasetBiasName = groupName + "_b";

    h5cpp::Group group = weightFile.root().open_group(groupName);

    h5cpp::Dataset dataset = group.open_dataset(datasetWeightName);
    h5cpp::Dataspace dataspace = dataset.get_dataspace();

    hsize_t weightDimensionArray[H5S_MAX_RANK];
    int weightDimensionCount = dataspace.get_dims(weightDimensionArray);

    std::vector<int> weightDimensions;
    for(int i = 0; i<weightDimensionCount; i++){
        weightDimensions.push_back(weightDimensionArray[i]);
    }

    std::vector<float> weightData(dataspace.get_npoints());
    dataset.read(&weightData[0]);

    //Bias
    dataset = group.open_dataset(datasetBiasName);
    dataspace = dataset.get_dataspace();

    hsize_t biasDimensionArray[H5S_MAX_RANK];
    int biasDimensionCount = dataspace.get_dims(biasDimensionArray);

    std::vector<int> biasDimensions;
    for(int i = 0; i<biasDimensionCount; i++){
        biasDimensions.push_back(biasDimensionArray[i]);
    }

    std::vector<float> biasData(dataspace.get_npoints());
    dataset.read(&biasData[0]);

    WeightWrapper output(weightDimensions, weightData, biasData, biasDimensions);

    return output;

}

void AlexNetWeightLoader::populateWeightsMap(){
    std::vector<WeightWrapper> layers;

    layers.push_back(createWeightWrapper("conv_1"));
    weightsMap.insert(std::pair<LayerIdentifier, WeightWrapper>(LayerIdentifier::CONV_1, layers.at(0)));


    layers.push_back(createWeightWrapper("conv_2_1"));
    layers.push_back(createWeightWrapper("conv_2_2"));

    layers.push_back(createWeightWrapper("conv_3"));
    weightsMap.insert(std::pair<LayerIdentifier, WeightWrapper>(LayerIdentifier::CONV_3, layers.at(3)));

    layers.push_back(createWeightWrapper("conv_4_1"));
    layers.push_back(createWeightWrapper("conv_4_2"));
    layers.push_back(createWeightWrapper("conv_5_1"));
    layers.push_back(createWeightWrapper("conv_5_2"));
    layers.push_back(createWeightWrapper("dense_1"));
    weightsMap.insert(std::pair<LayerIdentifier, WeightWrapper>(LayerIdentifier::FULLY_CON_1, layers.at(8)));

    layers.push_back(createWeightWrapper("dense_2"));
    weightsMap.insert(std::pair<LayerIdentifier, WeightWrapper>(LayerIdentifier::FULLY_CON_2, layers.at(9)));

    layers.push_back(createWeightWrapper("dense_3"));
    weightsMap.insert(std::pair<LayerIdentifier, WeightWrapper>(LayerIdentifier::FULLY_CON_3, layers.at(10)));

}

WeightWrapper AlexNetWeightLoader::getWeights(LayerIdentifier layerId) {
    return weightsMap.at(layerId);
}


AlexNetWeightLoader::AlexNetWeightLoader(const std::string &filePath)
        : filePath(filePath) {
    weightFile = h5cpp::File(filePath, "r");

    populateWeightsMap();

}

AlexNetWeightLoader::~AlexNetWeightLoader() = default;