//
// Created by michael on 07.01.18.
//

#include <iostream>
#include <vector>

#include "platforms/Platform.h"
#include "PlatformManager.h"

std::vector<Platform> PlatformManager::getPlatforms() {
    return std::vector<Platform>();
}

PlatformManager& PlatformManager::getInstance() {
    static PlatformManager instance;

    return instance;
}

std::vector<PlatformInfo> PlatformManager::getPlatformInfos() {
    return std::vector<PlatformInfo>();
}

