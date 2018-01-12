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

    /**
     * @brief Creates a WeightWrapper out of a given groupName from the internally stored weightFile.
     *
     * The method tries to access the group by using the groupName string. It will then load the weight and bias dataset
     * out of it and stores the data in one-dimensional std::vector objects. Furthermore it gets the dataset's
     * dimensions and stores everything in a WeightWrapper which will be returned.
     *
     * @param groupName A string representing the group name for which the WeightWrapper shall be created.
     * @return The created WeightWrapper.
     */
    WeightWrapper createWeightWrapper(const std::string &groupName);

    WeightWrapper appendLayers(const std::string &groupNameFirst, const std::string &groupNameSecond);

    void insertWeightWrapper(LayerIdentifier layerId, WeightWrapper weightWrapper);

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

    /**
     * @brief Returns the WeightWrapper corresponding to the LayerIdentifier parameter.
     *
     * The method looks up in the weightsMap which WeightWrapper is mapped to the layerId key and returns it.
     *
     * @param layerId The identification for the wanted WeightWrapper in the weightsMap.
     * @return The wanted WeightWrapper.
     */
    WeightWrapper getWeights(LayerIdentifier layerId) override;
};
