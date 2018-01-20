//
// Created by michael on 07.01.18.
//

#include "PlatformInfo.h"

PlatformInfo::PlatformInfo(const std::string &description, PlatformType type, const std::string &platformId,
                           int powerConsumption, int flops) : description(description), type(type),
                                                              platformId(platformId),
                                                              powerConsumption(powerConsumption), flops(flops) {}

const std::string &PlatformInfo::getDescription() const {
    return description;
}

PlatformType PlatformInfo::getType() const {
    return type;
}

const std::string &PlatformInfo::getPlatformId() const {
    return platformId;
}

int PlatformInfo::getPowerConsumption() const {
    return powerConsumption;
}

int PlatformInfo::getFlops() const {
    return flops;
}
