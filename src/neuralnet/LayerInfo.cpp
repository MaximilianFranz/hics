//
// Created by Maximilian Franz on 07.01.18.
//

#include <sstream>
#include "LayerInfo.h"
#include "../NotImplementedException.h"


LayerInfo::LayerInfo(std::string type, std::vector<int> inputDimensions, std::vector<int> outputDimensions)
        : type(type),
          inputDimensions(inputDimensions),
          outputDimensions(outputDimensions)
{
    //
}

LayerInfo::LayerInfo(std::string type, std::vector<int> &inputDimensions, std::vector<int> &outputDimensions,
                     int numFilters, std::vector<int> &filterDimensions, int zeroPadding, bool biased)
        : type(type),
          inputDimensions(inputDimensions),
          outputDimensions(outputDimensions),
          numFilters(numFilters),
          filterDimensions(filterDimensions),
          zeroPadding(zeroPadding),
          biased(biased)
{
    //
}

LayerInfo::LayerInfo(std::string type, std::vector<int> &inputDimensions, std::vector<int> &outputDimensions,
                     std::vector<int> &filterDimensions, int zeroPadding)
        : type(type),
          inputDimensions(inputDimensions),
          outputDimensions(outputDimensions),
          filterDimensions(filterDimensions),
          zeroPadding(zeroPadding),
{

}

std::string LayerInfo::getInfoString() {
    std::stringstream str;
    str << "This is a" << type << "layer";
    return str.str();
}

std::string LayerInfo::getInfoJSON() {
    throw NotImplementedException();
}

const std::string &LayerInfo::getType() const {
    return type;
}

const std::vector<int> &LayerInfo::getInputDimensions() const {
    return inputDimensions;
}

const std::vector<int> &LayerInfo::getOutputDimensions() const {
    return outputDimensions;
}

int LayerInfo::getNumFilters() const {
    return numFilters;
}

const std::vector<int> &LayerInfo::getFilterDimensions() const {
    return filterDimensions;
}

int LayerInfo::getZeroPadding() const {
    return zeroPadding;
}

bool LayerInfo::isBiased() const {
    return biased;
}
