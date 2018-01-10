//
// Created by David Culley on 07.01.18.
//

#include "AlexNetWeightLoader.h"
#include "../../../NotImplementedException.h"
#include "hdf_wrapper.h"


AlexNetWeightLoader::AlexNetWeightLoader(std::string filePath)
: filePath(filePath) {
    h5cpp::File file(filePath, "r");
    h5cpp::Group root = file.root();
    h5cpp::Group conv1 = root.open_group("conv_1");
    h5cpp::Dataset conv1W = conv1.open_dataset("conv_1_W");
    h5cpp::Dataspace conv1D = conv1W.get_dataspace();
    name = conv1D.get_name();
}

WeightWrapper AlexNetWeightLoader::getWeights(WeightLoader::LayerIdentifier layerId) {
    throw NotImplementedException();
}
