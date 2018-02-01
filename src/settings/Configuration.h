//
// Created by pselab on 30.01.18.
//

#pragma once

#include <string>


class Configuration {
private:
    const std::string SETTINGS_PATH = "../../../src/settings";

public:

    std::string get_model_path(std::string neuralNetIdentifier);

    std::string get_weights_path(std::string neuralNetIdentifier);

    std::string get_labels_path(std::string neuralNetIdentifier);
};


