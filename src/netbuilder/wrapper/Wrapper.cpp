//
// Created by michael on 09.01.18.
//

#include <NotImplementedException.h>
#include "Wrapper.h"

//TODO: Implement this considering convention for order of dimensions
float Wrapper::getElement(std::vector<int> location) {
    return 0;
}

Wrapper::Wrapper(int numDimensions, std::vector<int> &dimensionSizes, std::vector<float> &data)
        : numDimensions(numDimensions),
          dimensionSizes(dimensionSizes),
          data(data)
{
}

Wrapper::Wrapper(int numDimensions, std::vector<int> dimensionSizes) {
}

int Wrapper::getSizeOfDimension(int dim) {
    return this->dimensionSizes[dim-1];
}



