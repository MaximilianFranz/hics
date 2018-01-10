//
// Created by jallmenroeder on 07/01/18.
//

#ifndef HICS_CLASSIFICATIONRESULT_H
#define HICS_CLASSIFICATIONRESULT_H

#include "ImageResult.h"
#include "NetInfo.h"
#include "PerformanceData.h"
#include <string>


class ClassificationResult {
private:
    std::vector<ImageResult> results;
    NetInfo usedNet;
    PerformanceData performance;
    std::map<std::string, float> aggregatedResults;

public:
    ClassificationResult(const std::vector<ImageResult> &results, const NetInfo &usedNet,
                         const PerformanceData &performance);

    //Getter
    const std::vector<ImageResult> &getResults() const;
    const NetInfo &getUsedNeuralNet() const;
    const PerformanceData &getPerformance() const;
    const std::map<std::string, float> &getAggregatedResults() const;

    void aggregateResults();
};


#endif //HICS_CLASSIFICATIONRESULT_H
