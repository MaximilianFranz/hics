//
// Created by jallmenroeder on 07/01/18.
//

#pragma once


#include "PerformanceData.h"

class PerformanceCalculator {
public:

    /**
     * Calculates the performance of a finished classification
     * @param ptime         map with the time each platform took
     * @param totalTime     total computation time
     * @return              total performance data
     */
    static PerformanceData calculatePerformance(std::map<PlatformInfo, int> ptime, int totalTime);
};
