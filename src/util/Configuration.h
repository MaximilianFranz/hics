//
// Created by pselab on 27.02.18.
//

#pragma once

#include <string>


class Configuration {
private:
    static const std::string SETTINGS_PATH;
    static const std::string TESTING_PATH;
    /**
     * Checks the environment variable and sets the path respectively.
     *
     * @return a path to the folder with needed information for neural net's construction and image classifications
     */
    std::string choose_path();

public:

    /**
     * Provides the path to the folder which contains models of all provided neural nets.
     *
     * @return a path string to the models folder
     */
    static std::string get_model_path();

    /**
     * Provides the path to the folder which contains weights for all provided neural nets.
     *
     * @return a path to the weights folder
     */
    static std::string get_weights_path();

    /**
     * Provides the path to the folder which contains labels for all provided neural nets.
     *
     * @return a path to the labels folder
     */
    static std::string get_labels_path();

    /**
     * Provides the path to the model json of the required neural net by its identifier.
     *
     * @param neuralNetIdentifier
     * @return a path string to the net's model file
     */
    static std::string get_model_path(std::string neuralNetIdentifier);

    /**
     * Provides the path to the weights h5 file of the required neural net by its identifier.
     *
     * @param neuralNetIdentifier
     * @return a path string to the net's weights file
     */
    static std::string get_weights_path(std::string neuralNetIdentifier);

    /**
     * Provides the path to the labels txt file of the required neural net by its identifier.
     *
     * @param neuralNetIdentifier
     * @return a path string to the net's labels file
     */
    static std::string get_labels_path(std::string neuralNetIdentifier);


};