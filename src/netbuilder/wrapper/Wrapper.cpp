//
// Created by michael on 09.01.18.
//

#include <NotImplementedException.h>
#include "Wrapper.h"

//TODO: @Max: Redesign for new convention {channel, z, y, x}
const float Wrapper::getElement(std::vector<int> location) {
    unsigned long pos = 0;
    int i = 0;
    for (i; i <= getNumDimensions() - 2; i++) {
        pos += location[i]*(facultyOfDim(i));
    }
    pos += location[getNumDimensions() - 1];
    return data[pos];
}

unsigned long Wrapper::facultyOfDim(int dim) {
    unsigned long fac = 1;
    for (int i = getNumDimensions() - 1; i > dim; i--) {
        fac *= dimensions[i];
    }
    return fac;
}

Wrapper::Wrapper(std::vector<int> &dimensions, std::vector<float> &data)
        :
          dimensions(dimensions),
          data(data)
{
    // Calculate total number of elements once
    numElements = calcTotalNumElements();
}

Wrapper::Wrapper(std::vector<int> dimensions)
        : dimensions(dimensions),
          data(0)
{
    numElements = calcTotalNumElements();
    // data.reserve(numElements); //TODO: @Michael, this doesn't suffice (use this instead of line below an run test-case)
    data = std::vector<float>(numElements,0); //initialize 0-vector of required size - is in linear time
}

const int Wrapper::getSizeOfDimension(int dim) {
    return this->dimensions[dim-1];
}

unsigned long Wrapper::calcTotalNumElements() {
    numElements = 1;
    for (int dimSize : dimensions) {
        numElements *= dimSize;
    }
    return numElements;
}

const int Wrapper::getNumDimensions() {
    return (int)dimensions.size(); // cast is okay, because we don't deal with arbitrary dimensions.
}

const std::vector<int> Wrapper::getDimensions() {
    return dimensions;
}

const unsigned long Wrapper::getNumElements() {
    return numElements;
}

float *Wrapper::getDataArray() {
    return &data[0];
}

const std::vector<float> Wrapper::getData() {
    return data;
}

const float Wrapper::getElement(int x, int y, int rgb) {
    return getElement(std::vector<int>{rgb, y, x});
}



