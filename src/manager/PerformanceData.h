//
// Created by jallmenroeder on 07/01/18.
//

#pragma once


#include <PlatformInfo.h>
#include <map>
#include <vector>

/**
 * Wraps up data about the performance of a classification. This includes the power needed, the computation time and
 * the usage in percent each platform of a computation host took part in the computation.
 */
class PerformanceData {
private:
    int PowerConsumption;                                           /*!< power consumption of the computation in ws */
    int ComputationTime;                                            /*!< computation time of the classification in ms*/
    std::vector<std::pair<PlatformInfo, float>> platformUsage;      /*!< maps each platform to its percentage of the
 *                                                                       computation*/

public:
    /**
     * Creates a new PerformanceData object
     * @param PowerConsumption
     * @param ComputationTime
     * @param platformUsage
     */
    PerformanceData(int PowerConsumption, int ComputationTime,
                    const std::vector<std::pair<PlatformInfo, float>> &platformUsage);

    /**
     *
     * @return
     */
    int getPowerConsumption() const;

    /**
     *
     * @return
     */
    int getComputationTime() const;

    /**
     *
     * @return
     */
    const std::vector<std::pair<PlatformInfo, float>> &getPlatformUsage() const;
};
