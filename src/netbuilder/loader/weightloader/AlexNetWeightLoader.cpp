//
// Created by David Culley on 07.01.18.
//

#include "AlexNetWeightLoader.h"
#include "../../../NotImplementedException.h"
#include "hdf_wrapper.h"


AlexNetWeightLoader::AlexNetWeightLoader(std::string filePath)
: filePath(filePath) {
  
}

WeightWrapper AlexNetWeightLoader::getWeights(WeightLoader::LayerIdentifier layerId) {
    throw NotImplementedException();
}
