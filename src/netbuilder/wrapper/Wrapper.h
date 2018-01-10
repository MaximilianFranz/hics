//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <vector>
#include <list>

class Wrapper {

private:
    int calcTotalNumElements();
protected:

    std::vector<float> data;
    std::vector<int> dimensions;
    int numElements;

public:
    /**
     * Create Wrapper from given Data vector
     *
     * @param numDimensions
     * @param dimensions
     * @param data
     */
    Wrapper(std::vector<int> &dimensions, std::vector<float> &data);

    /**\brief Create empty Wrapper to store data in
     *
     * e.g. as output of a LayerFunction
     *
     * @param numDimensions
     * @param dimensionSizes
     */
    explicit Wrapper(std::vector<int> dimensionSizes);

    // pure virtual functions to make Wrapper an abstract class
    // TODO: easier if Wrapper implements basic functions

    /**
     * Get number of dimensions the data in this Wrapper has.
     *
     * @return number of dimensions.
     */
    virtual int getNumDimensions() {
        return (int)dimensions.size(); // cast is ok, since we won't be dealing with arbitrary dimension
    }

    /**
     * Get a vector with the size of each of the n dimensions.
     *
     * vector[n-1] is the size of the n-th dimension
     *
     * @return vector with the sizes of each dimension
     */
    virtual std::vector<int> getDimensionSizes() {
        return dimensions;
    }

    /**
     * Get total number of elements in the data vector
     *
     * @return total number of elements
     */
    virtual int getNumElements() {
        return numElements;
    }

    /**
     * Returns the data as a pointer to the raw array.
     *
     * This can be passed to OpenCL kernels and can be manipulated. It is passed by reference.
     *
     * @return pointer to the raw array
     */
    virtual float* getDataArray() {
        return &data[0];
    }

    /**
     * Get the vector object this Wrapper holds
     *
     * @return the vector object of the data.
     */
    virtual std::vector<float> getData() {
        return data;
    }

    /**
     * Returns the element at the specified location.
     *
     * Checks, whether location is a valid coordinate in the specified dimensions
     *
     * @param location of the element requested
     * @return the element at the specified location
     */
    virtual float getElement(std::vector<int> location);

    /**
     * \brief returns the size of the specified dimension iff dim smaller or equal to dimensions.size().
     *
     * Simpler version of getDimensionSizes
     *
     * @param dim for which we want the size
     * @return the size of the requested dimension.
     */
    virtual int getSizeOfDimension(int dim);



};
