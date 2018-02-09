//
// Created by Maximilian Franz on 23.01.18.
//

#pragma once

#include <string>
#include <vector>
#include <NetInfo.h>
#include "JSONModelLoader.h"

class ModelCrawler {
private:
    static NetInfo *constructNetInfo(JSONModelLoader *loader);

public:
    static std::vector<std::string> getFilesInDir(std::string pathToDir);

    static std::vector<NetInfo*> getValidNets(std::string path);


};

