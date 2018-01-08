//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <string>
#include <vector>

/**
 * Contains information on a layer. If some arguments are not applicable they assume default values.
 */
class LayerInfo {
private:
    std::string type;
    std::vector<int> inputDimensions;
    std::vector<int> outputDimensions;
    int numFilters;
    std::vector<int> filterDimensions;
    int zeroPadding; //TODO: changed from design doc
    bool bias;
    int stride;
public:
    std::string getInfoString();
    std::string getInfoJSON();





};


