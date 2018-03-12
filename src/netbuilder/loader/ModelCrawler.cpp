/* Copyright 2018 The HICS Authors
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall
 * be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 */

#include <dirent.h>
#include <iostream>
#include <cstring>
#include <ResourceException.h>

#include "ModelCrawler.h"

std::vector<std::string> ModelCrawler::getFilesInDir(std::string relPathToDir) {
    std::vector<std::string> results;
    char *resolved_path = realpath(relPathToDir.c_str(), nullptr);
    if (resolved_path == nullptr) {
        throw ResourceException("Path to model directory could not be resolved");
    }

    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir (resolved_path)) != nullptr) {
        // print all the files and directories within directory
        while ((ent = readdir (dir)) != nullptr) {
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
        throw ResourceException("Model directory was not found and could not be opened.");
    }

    free(resolved_path);

    return results;
}

std::vector<NetInfo *> ModelCrawler::getValidNets(std::string path) {
    std::vector<NetInfo*> validNets;
    std::vector<std::string> pathNames = getFilesInDir(path);


    for (const auto &filepath : pathNames) {
        // If file is a json
        if (filepath.find(".json") != std::string::npos) {
            // Create ModelLoader to perfom basic check whether model is a valid neural net model
            JSONModelLoader l(filepath);
            if (l.isValid()) {
                auto netInfo = constructNetInfo(&l);

                // identifier does not match name
                if (filepath.find(netInfo->getIdentifier() + ".json") == std::string::npos) {
                    throw ResourceException("filename in " + filepath + " does not match the identifier.");
                } else {
                    validNets.push_back(netInfo);
                }


            }
        }
    }

    if (validNets.empty()) {
        throw ResourceException("No valid description of a neural net found in models directory");
    }

    return validNets;
}

NetInfo* ModelCrawler::constructNetInfo(JSONModelLoader *loader) {
    std::string name = loader->getNetWorkName();
    std::string id = loader->getNetWorkID();
    int requiredDim = loader->getRequiredDimension();
    NetInfo *net = new NetInfo(name, requiredDim, id);
    return net;
}
