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

#pragma once

#include <vector>

//TODO: Add Class description to documentation.

class Wrapper {
protected:

    std::vector<float> data;
    std::vector<int> dimensions; /**! Order by convention: {channel, z, y, x} e.g. {96,3,11,11} for layer 1 */
    unsigned long numElements;

    unsigned long calcTotalNumElements();
    unsigned long facultyOfDim(int dim);
public:

    /**
     * Create Wrapper from given Data vector
     *
     * @param numDimensions
     * @param dimensions
     * @param data
     */
    Wrapper(std::vector<int> dimensions, std::vector<float> &data);

    /**\brief Create empty Wrapper to store data in. Reserves required size for dimensions.
     *
     * e.g. as output of a LayerFunction
     *
     * @param numDimensions
     * @param dimensionSizes
     */
    explicit Wrapper(std::vector<int> dimensionSizes);

    /**
     * Provide explicit Copy-constructor!
     *
     * @param wrapper
     */
    Wrapper(const Wrapper& wrapper);

    //TODO: Implement this correctly if needed!
//    Wrapper& operator= (const Wrapper& other);

    virtual ~Wrapper();

    /**
     * Get number of dimensions the data in this Wrapper has.
     *
     * @return number of dimensions.
     */
    const virtual int getNumDimensions();

    /**
     * Get a vector with the size of each of the n dimensions.
     *
     * vector[n-1] is the size of the n-th dimension
     *
     * @return vector with the sizes of each dimension
     */
    virtual std::vector<int> getDimensions() const;

    /**
     * Get total number of elements in the data vector
     *
     * @return total number of elements
     */
    virtual unsigned long getNumElements() const;

    /**
     * Returns the data as a pointer to the raw array.
     *
     * This can be passed to OpenCL kernels and can be manipulated. It is passed by reference.
     * This can be used when writing data to the vector, after instantiating it.
     *
     * @return pointer to the raw array
     */
    virtual float* getDataArray();

    const virtual float* getDataArray() const;


    /**
     * Get the vector object this Wrapper holds.
     * Only for reading since const.
     *
     * @return the vector object of the data.
     */
    virtual std::vector<float> getData() const;
    /**
     * Returns the element at the specified location.
     *
     * Checks, whether location is a valid coordinate in the specified dimensions.
     * Is const, so it can't be manipulated.
     *
     * @param location of the element requested
     * @return the element at the specified location
     */
    const virtual float getElement(std::vector<int> location);


    /**
     * Helper method to hide pointer arithmetic
     * @param x     x-coordinate
     * @param y     y-coordinate
     * @param rgb   rgb channel
     * @return float value of the pixel
     */
    const float getElement(int x, int y, int rgb);

    /**
     * \brief returns the size of the specified dimension iff dim smaller or equal to dimensions.size().
     *
     * Simpler version of getDimensionSizes
     *
     * @param dim for which we want the size
     * @return the size of the requested dimension.
     */
    const virtual int getSizeOfDimension(int dim);



};
