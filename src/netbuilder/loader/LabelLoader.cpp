//
// Created by Maximilian Franz on 22.01.18.
//

#include <fstream>
#include "LabelLoader.h"

std::map<int, std::string> LabelLoader::getLabelMap(std::string path) {

    std::map<int, std::string> labelMap;

    char resolved_path[1024];
    realpath(path.c_str(), resolved_path);
    std::ifstream file(resolved_path);
    std::string str;

    std::string line;

    int index = 0;

    while (std::getline(file, line)) {
        labelMap.emplace(std::pair<int, std::string>(index, line));
        index++;
    }

    return labelMap;

}
