//
// Created by pselab on 30.01.18.
//

#pragma once

#include <string>


class Configuration {
private:
    const std::string SETTINGS_PATH = "../../../src/settings";

public:

    /**
     * Provides the path to the model json of the required neural net by its identifier.
     * @param neuralNetIdentifier
     * @return a path string to the net's model file
     */
    std::string get_model_path(std::string neuralNetIdentifier);

    /**
     * Provides the path to the weights h5 file of the required neural net by its identifier.
     * @param neuralNetIdentifier
     * @return a path string to the net's weights file
     */
    std::string get_weights_path(std::string neuralNetIdentifier);

    /**
     * Provides the path to the labels txt file of the required neural net by its identifier.
     * @param neuralNetIdentifier
     * @return a path string to the net's labels file
     */
    std::string get_labels_path(std::string neuralNetIdentifier);

};


