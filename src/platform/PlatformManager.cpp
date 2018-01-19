//
// Created by michael on 07.01.18.
//

#include <iostream>
#include <vector>

#include "platforms/CpuPlatform.h"
#include "platforms/Platform.h"
#include "PlatformManager.h"

PlatformManager::PlatformManager() {
    // TODO: This needs to be more dynamic, e.g. OpenCL platforms need to be determined dynamically
    platforms.push_back(new CpuPlatform());
}

std::vector<Platform*> PlatformManager::getPlatforms() {
    return platforms;
}

PlatformManager& PlatformManager::getInstance() {
    static PlatformManager instance;

    return instance;
}

std::vector<PlatformInfo*> PlatformManager::getPlatformInfos() {
    return std::vector<PlatformInfo*>();
}

