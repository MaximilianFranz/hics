//
// Created by Maximilian Franz on 08.01.18.
//

#include "PlatformPlacer.h"

PlatformPlacer::PlatformPlacer() {
    // Better as pointer or directly as reference like:
//    this->platformManager = PlatformManager::getInstance();
    this->platformManager = &PlatformManager::getInstance();

}

std::vector<PlatformInfo *> PlatformPlacer::queryPlatforms() {
    return this->platformManager->getPlatformInfos();
}
