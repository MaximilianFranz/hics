//
// Created by pselab on 30.01.18.
//

#include "Configuration.h"


std::string Configuration::get_model_path(std::string neuralNetIdentifier) {
    return SETTINGS_PATH + "/" + neuralNetIdentifier + "/" + neuralNetIdentifier + ".json";;
}

std::string Configuration::get_weights_path(std::string neuralNetIdentifier) {
    return SETTINGS_PATH + "/" + neuralNetIdentifier + "/" + neuralNetIdentifier + "_weights.h5";
}

std::string Configuration::get_labels_path(std::string neuralNetIdentifier) {
    return SETTINGS_PATH + "/" + neuralNetIdentifier + "/" + neuralNetIdentifier + "_labels.txt";
}
