//
// Created by pselab on 30.01.18.
//

#include "Configuration.h"

const std::string Configuration::SETTINGS_PATH = "../../../resources";

std::string Configuration::get_model_path() {
    return SETTINGS_PATH + "/models";
}

std::string Configuration::get_weights_path() {
    return SETTINGS_PATH + "/weights";
}

std::string Configuration::get_labels_path() {
    return SETTINGS_PATH + "/labels";
}

std::string Configuration::get_model_path(std::string neuralNetIdentifier) {
    return get_model_path() + "/" + neuralNetIdentifier + ".json";
}

std::string Configuration::get_weights_path(std::string neuralNetIdentifier) {
    return get_weights_path() + "/" + neuralNetIdentifier + "_weights.h5";
}

std::string Configuration::get_labels_path(std::string neuralNetIdentifier) {
    return get_labels_path() + "/" + neuralNetIdentifier + "_labels.txt";
}
