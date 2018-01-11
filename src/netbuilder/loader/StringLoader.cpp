//
// Created by pselab on 11.01.18.
//

#include "StringLoader.h"
#include <fstream>

std::string std::StringLoader::getStringFromFile(std::string path) {
    std::ifstream file(path);
    std::string str;

    file.seekg(0, std::ios::end);
    str.reserve(static_cast<unsigned long>(file.tellg()));
    file.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(file)),
               std::istreambuf_iterator<char>());
    return str;
}