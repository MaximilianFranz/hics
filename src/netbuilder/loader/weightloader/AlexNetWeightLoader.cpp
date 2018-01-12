//
// Created by David Culley on 07.01.18.
//

#include "AlexNetWeightLoader.h"


WeightWrapper AlexNetWeightLoader::createWeightWrapper(const std::string &groupName){

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
    for(int i = 0; i<weightDimensionCount; i++){
        weightDimensions.push_back(weightDimensionArray[i]);
    }

    std::vector<float> weightData(dataspace.get_npoints());

    //Read and store the weightData in the float vector.
    dataset.read(&weightData[0]);

    //Open the bias dataset and dataspace.
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

WeightWrapper AlexNetWeightLoader::appendLayers(WeightWrapper* first, WeightWrapper* second){

    std::vector<float> firstWeights = first->getData();
    std::vector<float> secondWeights = second->getData();

    std::vector<float> firstBias = first->getBias();
    std::vector<float> secondBias = second->getBias();

    for(long i = 0;i<secondWeights.size();i++){
        firstWeights.push_back(secondWeights.at(i));
    }

    for(long i = 0; i<secondBias.size(); i++){
        firstBias.push_back(secondBias.at(i));
    }

    //TODO watch out maybe other dimension attributes need to be changed aswell.
    int firstWeightDimension = first->getDimensions().at(0) *= 2;

    std::vector<int> temp =  first->getDimensions();
    temp.at(0) = firstWeightDimension;

    std::vector<int> temp2;
    temp2.push_back((int)firstBias.size());

    WeightWrapper output(temp, firstWeights, firstBias, temp2);

    return output;
}

void AlexNetWeightLoader::populateWeightsMap(){
    std::vector<WeightWrapper> layers;

    layers.push_back(createWeightWrapper("conv_1"));
    weightsMap.insert(std::pair<LayerIdentifier, WeightWrapper>(LayerIdentifier::CONV_1, layers.at(0)));


    WeightWrapper temp1 = createWeightWrapper("conv_2_1");
    WeightWrapper temp2 = createWeightWrapper("conv_2_2");

    layers.push_back(appendLayers(&temp1, &temp2));
    weightsMap.insert(std::pair<LayerIdentifier, WeightWrapper>(LayerIdentifier::CONV_2, layers.at(1)));


    layers.push_back(createWeightWrapper("conv_3"));
    weightsMap.insert(std::pair<LayerIdentifier, WeightWrapper>(LayerIdentifier::CONV_3, layers.at(2)));

    temp1 = createWeightWrapper("conv_4_1");
    temp2 = createWeightWrapper("conv_4_2");

    layers.push_back(appendLayers(&temp1, &temp2));
    weightsMap.insert(std::pair<LayerIdentifier, WeightWrapper>(LayerIdentifier::CONV_4, layers.at(3)));

    temp1 = createWeightWrapper("conv_5_1");
    temp2 = createWeightWrapper("conv_5_2");

    layers.push_back(appendLayers(&temp1, &temp2));
    weightsMap.insert(std::pair<LayerIdentifier, WeightWrapper>(LayerIdentifier::CONV_5, layers.at(4)));


    layers.push_back(createWeightWrapper("dense_1"));
    weightsMap.insert(std::pair<LayerIdentifier, WeightWrapper>(LayerIdentifier::FULLY_CON_1, layers.at(5)));

    layers.push_back(createWeightWrapper("dense_2"));
    weightsMap.insert(std::pair<LayerIdentifier, WeightWrapper>(LayerIdentifier::FULLY_CON_2, layers.at(6)));

    layers.push_back(createWeightWrapper("dense_3"));
    weightsMap.insert(std::pair<LayerIdentifier, WeightWrapper>(LayerIdentifier::FULLY_CON_3, layers.at(7)));

}

WeightWrapper AlexNetWeightLoader::getWeights(LayerIdentifier layerId) {
    return weightsMap.at(layerId);
}


AlexNetWeightLoader::AlexNetWeightLoader(const std::string &filePath)
        : filePath(filePath) {
    weightFile = h5cpp::File(filePath, "r");

    populateWeightsMap();

}