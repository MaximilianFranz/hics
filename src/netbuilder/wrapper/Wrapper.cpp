//
// Created by michael on 09.01.18.
//

#include <NotImplementedException.h>
#include "Wrapper.h"

//TODO: Implement this considering convention for order of dimensions
float Wrapper::getElement(std::vector<int> location) {
    return 0;
}

Wrapper::Wrapper(std::vector<int> &dimensions, std::vector<float> &data)
        :
          dimensions(dimensions),
          data(data)
{
    // Calculate total number of elements once
    numElements = calcTotalNumElements();
}

Wrapper::Wrapper(std::vector<int> dimensionSizes) {
}

int Wrapper::getSizeOfDimension(int dim) {
    return this->dimensions[dim-1];
}

int Wrapper::calcTotalNumElements() {
    numElements = 1;
    for (int dimSize : dimensions) {
        numElements *= dimSize;
    }
}

int Wrapper::getNumDimensions() {
    return (int)dimensions.size(); // cast is okay, because we don't deal with arbitrary dimensions.
}

std::vector<int> Wrapper::getDimensions() {
    return dimensions;
}

int Wrapper::getNumElements() {
    return numElements;
}

float *Wrapper::getDataArray() {
    return &data[0];
}

std::vector<float> Wrapper::getData() {
    return data;
}



