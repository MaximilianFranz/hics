//
// Created by jallmenroeder on 07/01/18.
//

#pragma once

#include <string>
#include <map>
#include <vector>

#include <ImageResult.h>
#include <NetInfo.h>

#include "PerformanceData.h"

/**
 * Wraps up the data resulting from a classification.
 */
class ClassificationResult {
private:
    std::vector<ImageResult> results;               /*!< results of the classification*/
    NetInfo usedNet;                                /*!< neural net that was used for the computation*/
    PerformanceData performance;                    /*!< contains information about the performance*/
    std::vector<std::pair<std::string, float>> aggregatedResult;  /*!< contains the aggregated result*/

public:
    /**\brief Creates a new ClassificationResult.
     * The Classification Result can be used by the Manager to calculate overall performance and aggregate results.
     * It can then be displayed by the GUI.
     * @param results       results of the classification
     * @param usedNet       net that was used for the classification
     * @param performance   performance data of the classification
     */
    ClassificationResult(const std::vector<ImageResult> &results, const NetInfo &usedNet,
                         const PerformanceData &performance);

    //GETTER:
    /**
     * Accesses the results of the classification.
     * @return results
     */
    const std::vector<ImageResult> &getResults() const;

    /**
     * Accesses the used neural net.
     * @return neural net
     */
    const NetInfo &getUsedNeuralNet() const;

    /**
     * Accesses the performanceData of a computation host.
     * @return performance data
     */
    const PerformanceData &getPerformance() const;

    /**
     * Accesses the aggregated results if available.
     * @return aggregated results as a map with label and probability
     */
    const std::vector<std::pair<std::string, float>> &getAggregatedResults() const;

    /** \brief Aggregates the results.
     * Aggregates the results of the classification, meaning finding the 5 most probable labels that are on ALL images.
     */
    void aggregateResults();
};
