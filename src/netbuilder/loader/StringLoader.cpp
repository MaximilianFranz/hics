//
// Created by pselab on 11.01.18.
//

#include "StringLoader.h"
#include <fstream>


std::string StringLoader::getStringFromFile(std::string path) {
    char resolved_path[1024];
    realpath(path.c_str(), resolved_path);
    std::ifstream file(resolved_path);
    std::string str;

    file.seekg(0, std::ios::end);
    str.reserve(static_cast<unsigned long>(file.tellg()));
    file.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(file)),
               std::istreambuf_iterator<char>());
    return str;
}