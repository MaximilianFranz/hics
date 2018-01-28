//
// Created by Maximilian Franz on 23.01.18.
//

#include <dirent.h>
#include <iostream>
#include <cstring>

#include "ModelCrawler.h"
#include "ModelLoader.h"
#include "JSONModelLoader.h"

//TAKES relative PATHS
std::vector<std::string> ModelCrawler::getFilesInDir(std::string relPathToDir) {
    std::vector<std::string> results;
    char resolved_path[1024];
    realpath(relPathToDir.c_str(), resolved_path);

    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir (resolved_path)) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            //Remove "." and ".." entries which occur often.
            if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0 ) {
                std::string filename = ent->d_name;
                std::string fullPath = relPathToDir + "/" + filename;
                results.push_back(fullPath);

            }
            else {
                continue;
            }

        }
        closedir (dir);
    } else {
        /* could not open directory */
    }
    return results;
}

std::vector<NetInfo *> ModelCrawler::getValidNets(std::string path) {
    std::vector<NetInfo*> validNets;
    std::vector<std::string> pathNames = getFilesInDir(path);


    for (const auto &filepath : pathNames) {
        // If file is a json
        if (filepath.find(".json") != std::string::npos) {
            // Create ModelLoader to perfom basic check whether model is a valid neuralnet model
            JSONModelLoader l(filepath);
            if (l.isValid()) {
                validNets.push_back(constructNetInfo(&l));
            }
        }
    }

    return validNets;
}

NetInfo *ModelCrawler::constructNetInfo(JSONModelLoader *loader) {
    std::string name = loader->getNetWorkName();
    std::string id = loader->getNetWorkID();
    int requiredDim = loader->getRequiredDimension();
    NetInfo *net = new NetInfo(name, requiredDim, id);
    return net;
}
