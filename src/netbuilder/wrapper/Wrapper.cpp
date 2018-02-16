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

Wrapper::Wrapper(std::vector<int> dimensions, std::vector<float> &data)
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

std::vector<int> Wrapper::getDimensions() const {
    return dimensions;
}

unsigned long Wrapper::getNumElements() const {
    return numElements;
}

float *Wrapper::getDataArray() {
    return &data[0];
}

const float *Wrapper::getDataArray() const {
    return &data[0];
}

std::vector<float> Wrapper::getData() const {
    return data;
}

const float Wrapper::getElement(int x, int y, int rgb) {
    return getElement(std::vector<int>{rgb, y, x});
}

Wrapper::Wrapper(const Wrapper &wrapper)
        : data(wrapper.data),
          dimensions(wrapper.dimensions),
          numElements(wrapper.numElements) {

}

//Wrapper &Wrapper::operator=(const Wrapper &other) {
//    throw NotImplementedException();
//}

Wrapper::~Wrapper() {
    // No Destructor yet
//    delete[](&data);
//    delete[](&dimensions);
//    delete[](&numElements);
}



