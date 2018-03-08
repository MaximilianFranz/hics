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
    NetInfo getUsedNeuralNet() const;

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
