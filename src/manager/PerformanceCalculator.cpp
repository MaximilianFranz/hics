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

#include "PerformanceCalculator.h"
#include "HostPlacer.h"


PerformanceData
PerformanceCalculator::calculatePerformance(std::vector<hostPlatformDistribution> &platformDist,
                                          std::vector<HostInfo*> &hostDistribution) {
    //Set the usage percentages from relative to host to relative to whole classification
    int computationTime = 0;
    int powerConsumption = 0;
    std::vector<std::pair<PlatformInfo*, float>> overallDistribution;

    for (int i = 0; i < platformDist.size(); i++) {
        auto host = platformDist.begin() + i;
        for (auto platform : host.operator*()) {
            platform.second = platform.second * hostDistribution[i]->usage;
            overallDistribution.push_back(platform);
        }
        host++;
    }
    //find the slowest host, this is the total computation time
    //add the power each host took to add up the power consumption
    for (auto host : hostDistribution) {
        computationTime = std::max(computationTime, host->time);

        auto hostData = HostPlacer::readComputationHostInfo(host->jsonName);
        float powerPerTime = float(hostData.powerConsumption) / float(hostData.timeConsumption);
        powerConsumption += powerPerTime * host->time;
    }
    //mw * ms = 10^-3 mWs
    //convert powerconsumption from mw * ms to mWs
    powerConsumption = powerConsumption / 1000;

    return PerformanceData(powerConsumption, computationTime, overallDistribution);


}
