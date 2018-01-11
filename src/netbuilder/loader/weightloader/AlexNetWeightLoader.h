//
// Created by David Culley on 07.01.18.
//

#pragma once

#include "hdf_wrapper.h"
#include "loader/weightloader/WeightLoader.h"
#include <string>
#include <map>


class AlexNetWeightLoader : public WeightLoader {

private:

    const std::string filePath;
    h5cpp::File weightFile;
    std::map<LayerIdentifier, WeightWrapper> weightsMap;

    WeightWrapper createWeightWrapper(const std::string &groupName);
    void populateWeightsMap();

public:

    /**
    * @brief Initializes the AlexNetWeightLoader with the given weight file.
    *
    * The constructor will try to load the weights from the given filePath and will then save the weights in the
     * weightsMap. Each Layer will get a WeightWrapper and will be identified with the LayerIdentifier enumerate.
    *
    * @param filePath The weight file for the AlexNet in HDF5 format.
    */
    explicit AlexNetWeightLoader(const std::string &filePath);

    virtual WeightWrapper getWeights(WeightLoader::LayerIdentifier layerId);

    virtual ~AlexNetWeightLoader();


};
