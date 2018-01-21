//
// Created by michael on 07.01.18.
//

#pragma once

#include <vector>

#include "platforms/Platform.h"
#include "PlatformInfo.h"

class PlatformManager {
private:
    // Private constructor
    PlatformManager();
    std::vector<Platform*> platforms;

public:
    // https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
    PlatformManager(PlatformManager const&) = delete;
    PlatformManager& operator=(PlatformManager const &) = delete;

    static PlatformManager& getInstance();

    std::vector<Platform*> getPlatforms();

    std::vector<PlatformInfo*> getPlatformInfos();
};
