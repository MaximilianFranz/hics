//
// Created by jallmenroeder on 07/01/18.
//

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
    //add the power each Host took to add up the power consumption
    for (auto host : hostDistribution) {
        computationTime = std::max(computationTime, host->time);

        auto hostData = HostPlacer::readComputationHostInfo(host->jsonName);
        float powerPerTime = float(hostData.powerConsumption) / float(hostData.timeConsumption);
        powerConsumption += powerPerTime * host->time;
    }

    return PerformanceData(powerConsumption, computationTime, overallDistribution);


}
