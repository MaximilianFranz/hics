//
// Created by jallmenroeder on 07/01/18.
//

#pragma once


#include <ComputationHost.h>

class Client : ComputationHost {
    Client();

    std::vector<ImageResult> classify(std::vector<ImageWrapper> images, NetInfo net, OperationMode mode,
                                      std::vector<PlatformInfo> selectedPlatforms) override;

    std::vector<PlatformInfo> queryPlatform() override;

    std::vector<NetInfo> queryNets() override;

};
