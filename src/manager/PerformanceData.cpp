//
// Created by jallmenroeder on 07/01/18.
//

#include "PerformanceData.h"

PerformanceData::PerformanceData(int PowerConsumption, int ComputationTime,
                                 const std::map<PlatformInfo, float> &platformUsage) : PowerConsumption(
        PowerConsumption), ComputationTime(ComputationTime), platformUsage(platformUsage) {}

int PerformanceData::getPowerConsumption() const {
    return PowerConsumption;
}

int PerformanceData::getComputationTime() const {
    return ComputationTime;
}

const std::map<PlatformInfo, float> &PerformanceData::getPlatformUsage() const {
    return platformUsage;
}
