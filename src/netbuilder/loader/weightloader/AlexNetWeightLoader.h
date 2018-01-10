//
// Created by David Culley on 07.01.18.
//

#pragma once

#include "WeightLoader.h"
#include <string>

class AlexNetWeightLoader : public WeightLoader {
private:

    std::string filePath;
    std::string name;

public:
    /**
    * @brief Initializes the AlexNetWeightLoader with the given weight file.
    *
    * The constructor will try to load the weights from the given filePath and will then save the weights in the
     * weightsMap. Each Layer will get a WeightWrapper and will be identified with the LayerIdentifier enumerate.
    *
    * @param filePath The weight file for the AlexNet in HDF5 format.
    */
    AlexNetWeightLoader(std::string filePath);

    WeightWrapper getWeights(LayerIdentifier layerId) override;

    std::string getName(){
        return name;
    }
};
