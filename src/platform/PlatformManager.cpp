/* Copyright 2018 The HICS Authors
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall
 * be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 */

#include <iostream>
#include <fstream>
#include <vector>

#include <json.hpp>

#include "platforms/CpuPlatform.h"
#include "platforms/FpgaPlatform.h"
#include "platforms/ClPlatform.h"
#include "platforms/Platform.h"
#include "PlatformManager.h"

using json = nlohmann::json;

PlatformManager::PlatformManager() {
    std::ifstream i(RES_DIR "platforms.json");
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
#ifdef ALTERA
        } else if (type == "FPGA") {
            PlatformInfo pi(desc, PlatformType::FPGA, uuid, power, flops);
            platforms.push_back(new FpgaPlatform(pi));
#else
        } else if (type == "GPU") {
            PlatformInfo pi(desc, PlatformType::GPU, uuid, power, flops); // LCOV_EXCL_LINE
            platforms.push_back(new ClPlatform(pi));                      // LCOV_EXCL_LINE
        } else if (type == "CL_CPU") {
            PlatformInfo pi(desc, PlatformType::CL_CPU, uuid, power, flops);
            platforms.push_back(new ClPlatform(pi));
#endif
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
    // In case we don't find a platform for the given uuid, we return
    // a nullptr, which means the result should be checked by the caller.
    return nullptr;
}
