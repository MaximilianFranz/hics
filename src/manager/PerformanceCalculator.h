//
// Created by jallmenroeder on 07/01/18.
//

#pragma once


#include "PerformanceData.h"
#include <PlatformInfo.h>

typedef std::vector<std::pair<PlatformInfo, float>> hostPlatformDistribution;

/**
 * Calculates the performance of a classification according to the time each platform took to calculate.
 */
class PerformanceCalculator {
public:
    struct HostInfo {
        std::string jsonName;
        float usage;
        int time;

        HostInfo(std::string name, float usage, int time) : jsonName(name), usage(usage), time(time) {}
    };

    /**
     * Calculates the performance of a finished classification
     * @param ptime         map with the time each platform took
     * @param totalTime     total computation time
     * @return              total performance data
     */
    static PerformanceData calculatePerformance(std::vector<hostPlatformDistribution> &platformDist,
                                              std::vector<HostInfo> &hostDistribution);
};
