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

#include "ModelCrawler.h"
#include "ModelLoader.h"
#include "JSONModelLoader.h"

//TAKES relative PATHS
std::vector<std::string> ModelCrawler::getFilesInDir(std::string relPathToDir) {
    std::vector<std::string> results;
    char *resolved_path = realpath(relPathToDir.c_str(), NULL);
    // TODO: check if resolved_path is NULL

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

    free(resolved_path);

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
