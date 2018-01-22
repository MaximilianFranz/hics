//
// Created by jallmenroeder on 07/01/18.
//

#include <algorithm>
#include <functional>
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

const std::vector<std::pair<std::string, float>> &ClassificationResult::getAggregatedResults() const {
    return aggregatedResult;
}


bool isEqual(const std::pair<std::string, float>& element1, const std::pair<std::string, float>& element2) {
    return element1.first == element2.first;
}

void ClassificationResult::aggregateResults() {

    for (auto const &imageIt : results) {

        for (auto resultIt : imageIt.getResults()) {
            std::string label = resultIt.first;

            //MAGIC  checks if a label is already added to the vector
            auto currentElement = std::find_if(aggregatedResult.begin(), aggregatedResult.end(),
                                               [&label](std::pair<std::string, float>& element){
                                                   return element.first == label;
                                               });

            //insert label if new, sum up probability otherwise
            if (currentElement == aggregatedResult.end()) {

                aggregatedResult.push_back(resultIt);
            } else {
                currentElement.operator*().second += resultIt.second;
            }

        }
    }

    auto aggIt = aggregatedResult.begin();
    for (aggIt; aggIt != aggregatedResult.end(); ++aggIt) {
        aggIt.operator*().second = aggIt.operator*().second/results.size();
    }

    aggregatedResult.erase(aggregatedResult.begin() + 5, aggregatedResult.end());

    std::sort(aggregatedResult.begin(), aggregatedResult.end(), [](const std::pair<std::string, float> &left,
                                                                   const std::pair<std::string, float> &right) {
        return left.second > right.second;
    });
}


