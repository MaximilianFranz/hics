//
// Created by David Culley on 07.01.18.
//

#include "AlexNetWeightLoader.h"
#include "../../../NotImplementedException.h"


using namespace h5cpp;

WeightWrapper AlexNetWeightLoader::createWeightWrapper(const std::string &groupName){
    std::string datasetWeightName = groupName + "_W";
    std::string datasetBiasName = groupName + "_b";

    Group group = weightFile.root().open_group(groupName);

    Dataset dataset = group.open_dataset(datasetWeightName);
    Dataspace dataspace = dataset.get_dataspace();

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

AlexNetWeightLoader::AlexNetWeightLoader(std::string filePath)
: filePath(filePath) {
  weightFile = File(filePath, "r");
}




WeightWrapper AlexNetWeightLoader::getWeights(WeightLoader::LayerIdentifier layerId) {
    throw NotImplementedException();
}



File file("/home/pselab/Dokumente/repo/hics/src/netbuilder/loader/weightloader/alexnet_weights.h5", "r");
Group root = file.root();

Group conv1 = root.open_group("conv_1");

Dataset conv1W = conv1.open_dataset("conv_1_W");
Dataset conv1b = conv1.open_dataset("conv_1_b");

Dataspace ds = conv1W.get_dataspace();
Dataspace ds2 = conv1b.get_dataspace();

hsize_t dims[H5S_MAX_RANK];
int rank = ds.get_dims(dims);

hsize_t dims2[H5S_MAX_RANK];
int rank2 = ds2.get_dims(dims2);

std::setprecision(20);

std::vector<float> data(ds2.get_npoints());

conv1b.read<float>(&data[0]);

std::cout << "dataset = ";
int i = 0;
for (auto it = data.begin(); it != data.end(); ++it)
{
std::cout << *it << std::endl;
std::cout << "--" << i << "--" << std::endl;
i++;
}
std::cout << std::endl;
