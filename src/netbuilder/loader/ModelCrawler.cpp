//
// Created by Maximilian Franz on 23.01.18.
//

#include <dirent.h>
#include "ModelCrawler.h"

//TAKES relative PATHS
std::vector<std::string> ModelCrawler::getFilesInDir(std::string relPathToDir) {
    std::vector<std::string> results;
    char resolved_path[1024];
    realpath(relPathToDir.c_str(), resolved_path);

    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir (resolved_path)) != nullptr) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != nullptr) {
            std::string filename = ent->d_name;
            results.push_back(filename);
        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("");
        return results;
    }
}
