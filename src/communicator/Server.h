//
// Created by jallmenroeder on 07/01/18.
//

#pragma once


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
