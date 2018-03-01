//
// Created by pselab on 27.02.18.
//

#include "Configuration.h"


const std::string Configuration::SETTINGS_PATH = "../../../resources";
const std::string Configuration::TESTING_PATH = "";
char* environment = NULL;

std::string Configuration::choose_path() {
    if (std::getenv(environment) == "testing") {
        return TESTING_PATH;
    }
    else {
        return SETTINGS_PATH;
    }
}

std::string Configuration::get_model_path() {
    return choose_path() + "/models";
}

std::string Configuration::get_weights_path() {
    return choose_path() + "/weights";
}

std::string Configuration::get_labels_path() {
    return choose_path() + "/labels";
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