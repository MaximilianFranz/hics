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

#include "PlatformInfo.h"

PlatformInfo::PlatformInfo() {}

PlatformInfo::PlatformInfo(const std::string &description,
                           PlatformType type,
                           const std::string &platformId,
                           int powerConsumption,
                           int flops) :
        description(description),
        type(type),
        platformId(platformId),
        powerConsumption(powerConsumption),
        flops(flops) {}

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
