//
// Created by jallmenroeder on 07/01/18.
//

#ifndef HICS_SERVER_H
#define HICS_SERVER_H


#include <ImageResult.h>
#include <PlatformInfo.h>
#include <NetInfo.h>

class Server {
public:
    void init();

    std::vector<ImageResult> classifyRequest();
    std::vector<PlatformInfo> queryPlatformsRequest();
    std::vector<NetInfo> queryNetsRequest();
};


#endif //HICS_SERVER_H
