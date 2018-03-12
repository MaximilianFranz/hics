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

#include <algorithm>
#include <functional>
#include "ClassificationResult.h"

ClassificationResult::ClassificationResult(const std::vector<ImageResult> &results, const NetInfo &usedNet,
                                           const PerformanceData &performance)
        : results(results), usedNet(usedNet), performance(performance) {}

const std::vector<ImageResult> &ClassificationResult::getResults() const {
    return results;
}

NetInfo ClassificationResult::getUsedNeuralNet() const {
    return usedNet;
}

const PerformanceData &ClassificationResult::getPerformance() const {
    return performance;
}

const std::vector<std::pair<std::string, float>> &ClassificationResult::getAggregatedResults() const {
    return aggregatedResult;
}

void ClassificationResult::aggregateResults() {

    for (auto const &imageIt : results) {

        for (auto resultIt : imageIt.getResults()) {
            std::string label = resultIt.first;

            //checks if a label is already added to the vector
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

    //divide by the number of results to get the relative probability
    for (auto aggIt = aggregatedResult.begin(); aggIt != aggregatedResult.end(); ++aggIt) {
        aggIt.operator*().second = aggIt.operator*().second/results.size();
    }

    //remove everything over 5 labels
    aggregatedResult.erase(aggregatedResult.begin() + 5, aggregatedResult.end());

    //sort according to new probability
    std::sort(aggregatedResult.begin(), aggregatedResult.end(), [](const std::pair<std::string, float> &left,
                                                                   const std::pair<std::string, float> &right) {
        return left.second > right.second;
    });
}


