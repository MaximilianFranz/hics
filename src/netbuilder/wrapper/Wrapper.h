//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <vector>
#include <list>

class Wrapper {
protected:

    std::vector<float> data;
    int numDimensions;
    std::vector<int> dimensionSizes;
    int numElements;

public:
    /**
     * Create Wrapper from given Data vector
     *
     * @param numDimensions
     * @param dimensionSizes
     * @param data
     */
    Wrapper(int numDimensions, std::vector<int> &dimensionSizes, std::vector<float> &data);

    /**\brief Create empty Wrapper to store data in
     *
     * e.g. as output of a LayerFunction
     *
     * @param numDimensions
     * @param dimensionSizes
     */
    Wrapper(int numDimensions, std::vector<int> dimensionSizes);

    // pure virtual functions to make Wrapper an abstract class
    // TODO: easier if Wrapper implements basic functions


    virtual int getNumDimensions() {
        return numDimensions;
    }

    virtual std::vector<int> getDimensionSizes() {
        return dimensionSizes;
    }

    virtual int getNumElements() {
        return numElements;
    }

    virtual float* getDataArray() {
        return &data[0];
    }

    virtual std::vector<float> getData() {
        return data;
    }

    virtual float getElement(std::vector<int> location);

    virtual int getSizeOfDimension(int dim);



};
