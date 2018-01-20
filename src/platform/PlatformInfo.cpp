//
// Created by michael on 07.01.18.
//

#include "PlatformInfo.h"

PlatformInfo::PlatformInfo() {}

PlatformInfo::PlatformInfo(const std::string &string, const std::string &platformId, float powerConsumption, int flops)
        : string(string), platformId(platformId), powerConsumption(powerConsumption), flops(flops) {}

const std::string &PlatformInfo::getString() const {
    return string;
}

const std::string &PlatformInfo::getPlatformId() const {
    return platformId;
}

float PlatformInfo::getPowerConsumption() const {
    return powerConsumption;
}

int PlatformInfo::getFlops() const {
    return flops;
}
