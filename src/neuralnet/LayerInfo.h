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

public:
    std::string type;
    std::vector<int> inputDimensions; /**! @see Wrapper for convention of order**/
    std::vector<int> outputDimensions; /**! @see Wrapper for conventions of order**/
    int numFilters;
    std::vector<int> filterDimensions;
    int zeroPadding; //TODO: changed from design doc
    bool bias;

    std::string getInfoString();
    std::string getInfoJSON();

    LayerInfo();




};


