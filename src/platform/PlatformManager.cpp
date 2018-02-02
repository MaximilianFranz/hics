//
// Created by michael on 07.01.18.
//

#include <iostream>
#include <fstream>
#include <vector>

#include <json.hpp>

#include "platforms/CpuPlatform.h"
#include "platforms/Platform.h"
#include "PlatformManager.h"

using json = nlohmann::json;

PlatformManager::PlatformManager() {
    std::ifstream i("../../../resources/platforms.json");
    json j;
    i >> j;

    for (auto it : j["platforms"]) {
        std::string type = it["type"];
        std::string desc = it["description"];
        std::string uuid = it["uuid"];
        float power = it["power_consumption"];
        int flops = it["flops"];

        if (type == "CPU") {
            // TODO: validate if given platform matches the actual CPU on the host
            PlatformInfo pi(desc, PlatformType::CPU, uuid, power, flops);
            platforms.push_back(new CpuPlatform(pi));
        } else if (type == "FPGA") {
            // TODO: needs FPGA implementation and CL context
        } else if (type == "GPU") {
            // TODO: needs GPU implementtion and CL context
        }

    }

}

std::vector<Platform*> PlatformManager::getPlatforms() {
    return platforms;
}

PlatformManager& PlatformManager::getInstance() {
    static PlatformManager instance;

    return instance;
}

std::vector<PlatformInfo*> PlatformManager::getPlatformInfos() {
    std::vector<PlatformInfo*> infos;
    for (auto p : platforms) {
        infos.push_back(&(p->getPlatformInfo()));
    }
    return infos;
}

Platform* PlatformManager::getPlatformById(std::string uuid) {
    for (auto p : platforms) {
        if (p->getPlatformInfo().getPlatformId() == uuid)
            return p;
    }
}
