//
// Created by jallmenroeder on 07/01/18.
//

#ifndef HICS_CLIENT_H
#define HICS_CLIENT_H


#include <ComputationHost.h>

class Client : ComputationHost {
    Client();

    std::vector<ImageResult> classify(std::vector<ImageWrapper> images, NetInfo net, OperationMode mode,
                                      std::vector<PlatformInfo> selectedPlatforms) override;

    std::vector<PlatformInfo> queryPlatform() override;

    std::vector<NetInfo> queryNets() override;

};


#endif //HICS_CLIENT_H
