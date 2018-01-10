//
// Created by jallmenroeder on 07/01/18.
//

#include "ClassificationResult.h"

ClassificationResult::ClassificationResult(const std::vector<ImageResult> &results, const NetInfo &usedNet,
                                           const PerformanceData &performance)
        : results(results), usedNet(usedNet), performance(performance) {}

const std::vector<ImageResult> &ClassificationResult::getResults() const {
    return results;
}

const NetInfo &ClassificationResult::getUsedNeuralNet() const {
    return usedNet;
}

const PerformanceData &ClassificationResult::getPerformance() const {
    return performance;
}

const std::map<std::string, float> &ClassificationResult::getAggregatedResults() const {
    return aggregatedResults;
}

void ClassificationResult::aggregateResults() {
    //TODO: Implementation of aggregateResults
}
