//
// Created by pselab on 11.01.18.
//

#include "StringLoader.h"
#include <fstream>

<<<<<<< HEAD
std::string StringLoader::getStringFromFile(std::string path) {
    std::ifstream file(path);
=======
std::string std::StringLoader::getStringFromFile(std::string path) {
    char resolved_path[1024];
    realpath(path.c_str(), resolved_path);
    std::ifstream file(resolved_path);
>>>>>>> 749e4a1441905d3c72b506dda5913fb5ee829312
    std::string str;

    file.seekg(0, std::ios::end);
    str.reserve(static_cast<unsigned long>(file.tellg()));
    file.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(file)),
               std::istreambuf_iterator<char>());
    return str;
}