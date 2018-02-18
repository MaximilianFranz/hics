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

#include <IllegalArgumentException.h>
#include "ConvolutionLayer.h"

const int X_DIM = 2;
const int Y_DIM = 1;
const int Z_DIM = 0;




ConvolutionLayer::ConvolutionLayer(int numFilters, int filterSize, int zeroPadding, int stride, int numGroups,
                                   std::vector<int> &inputDimensions)
        : numFilters(numFilters),
          filterSize(filterSize),
          zeroPadding(zeroPadding),
          stride(stride),
          numGroups(numGroups)
{
    this->inputDimensions = inputDimensions;
    this->type = CONVOLUTION;
    this->outputDimensions = calcOutputDimensions();
    init(); // TODO never call virtual functions in constructor
}

ConvolutionLayer::ConvolutionLayer(int numFilters, int filterSize, int zeroPadding, int stride, int numGroups,
                                   std::vector<int> &inputDimensions, WeightWrapper *weights)
        : numFilters(numFilters),
          filterSize(filterSize),
          zeroPadding(zeroPadding),
          stride(stride),
          numGroups(numGroups),
          weights(weights)
{
    this->inputDimensions = inputDimensions;
    this->type = CONVOLUTION;
    this->outputDimensions = calcOutputDimensions();
    init(); // TODO never call virtual functions in constructor
}

std::vector<int> ConvolutionLayer::calcOutputDimensions() {
    int outputWidth;
    std::vector<int> outDim(3); // three dimensional output
    if (stride == 1) {
        outputWidth = inputDimensions[D3_X_DIM];
    }
    else {
        outputWidth = ((this->inputDimensions[D3_X_DIM] - filterSize) / stride) + 1;
    }
    outDim[X_DIM] = outputWidth; // X, Y are the same!
    outDim[Y_DIM] = outputWidth;
    outDim[Z_DIM] = numFilters;
    return outDim;

}

void ConvolutionLayer::forward() {
    if (numGroups > 2) {

        computed = false;
        throw IllegalArgumentException("Convolution not implemented for more than two groups.");

    } else if (numGroups == 2) {

        forwardSplit();

    } else {

        outputWrapper = new DataWrapper(getOutputDimensions());
        this->function->execute(*previousLayer->getOutputWrapper(),
                                *outputWrapper,
                                *weights,
                                stride,
                                filterSize,
                                numFilters,
                                zeroPadding);
    }
    computed = true;
}

// HELPER methods

//TODO: Move this somewhere else
std::vector<int> ConvolutionLayer::splitDim(std::vector<int> in, int factor, int index) {
    std::vector<int> out;
    for (int i = 0; i < in.size(); i++) {
        if (i == index) {
            out.push_back(in.at(i)/factor);
        }
        else {
            out.push_back(in.at(i)/1); // No idea why, but with /1 it works
        }
    }
    return out;
}

WeightWrapper* ConvolutionLayer::getSecondHalf(WeightWrapper* weights) {
    std::vector<float> weightData = weights->getData();
    std::vector<float> biasData = weights->getBias();

    // Get second half of weights
    auto middleIter = weightData.begin();
    std::advance(middleIter, weightData.size()/2);
    std::vector<float> weightDataSecond(middleIter, weightData.end());

    // Get second half of bias
    middleIter = biasData.begin();
    std::advance(middleIter, biasData.size()/2);
    std::vector<float> biasDataSecond(middleIter, biasData.end());

    //Split first two dimensions of the weights in half
    WeightWrapper *weightsSecond = new WeightWrapper(splitDim(splitDim(weights->getDimensions(), 2, 0), 2, 1),
                                weightDataSecond,
                                biasDataSecond,
                                splitDim(weights->getBiasDimension(), 2, 0));
    return weightsSecond;

}

DataWrapper* ConvolutionLayer::getSecondHalf(DataWrapper* input) {
    std::vector<float> inputDataFull = input->getData();
    auto middleIter = inputDataFull.begin();
    std::advance(middleIter, inputDataFull.size()/2);
    std::vector<float> inputDataSecond(middleIter, inputDataFull.end());
    DataWrapper *secondHalf = new DataWrapper(splitDim(input->getDimensions(), 2, 0), inputDataSecond);

    return secondHalf;

}

void ConvolutionLayer::forwardSplit() {
    // PREPARE FIRST GROUPT EXECUTION
    DataWrapper* input = previousLayer->getOutputWrapper();
    std::vector<float> in = input->getData();

    // It's sufficient to split dimensions here, because of how the data is accessed.
    DataWrapper *firstHalfIn = new DataWrapper(splitDim(input->getDimensions(), 2, 0), in);
    DataWrapper* firstHalfOut = new DataWrapper(splitDim(outputDimensions, 2, 0));

    //  EXECUTION of first half: weights are handed in completely, but only first half is touched.
    this->function->execute(*firstHalfIn,
                            *firstHalfOut,
                            *weights,
                            stride,
                            filterSize,
                            numFilters / 2,
                            zeroPadding);

    WeightWrapper *secondHalfWeights = getSecondHalf(weights);

    DataWrapper *secondHalfIn = getSecondHalf(input);
    DataWrapper *secondHalfOut = new DataWrapper(splitDim(getOutputDimensions(), 2, 0));

    //EXECUTION of second half
    this->function->execute(*secondHalfIn,
                            *secondHalfOut,
                            *secondHalfWeights,
                            stride,
                            filterSize,
                            numFilters / 2,
                            zeroPadding);

    std::vector<float> firstOutData = firstHalfOut->getData();
    std::vector<float> secondOutData = secondHalfOut->getData();

    //Merging two groups
    firstOutData.insert(firstOutData.end(), secondOutData.begin(), secondOutData.end());

    outputWrapper = new DataWrapper(getOutputDimensions(), firstOutData);

    //clean up additionally created DataWrappers after execution.
    delete secondHalfIn;
    delete secondHalfOut;
    delete firstHalfIn;
    delete firstHalfOut;

}

// GETTER and SETTER methods

int ConvolutionLayer::getNumFilters() const {
    return numFilters;
}

int ConvolutionLayer::getFilterSize() const {
    return filterSize;
}

int ConvolutionLayer::getZeroPadding() const {
    return zeroPadding;
}

int ConvolutionLayer::getStride() const {
    return stride;
}

void ConvolutionLayer::setFunction(ConvolutionFunction *function) {
    this->function = function;
    this->functionSet =true;
}

void ConvolutionLayer::setWeights(WeightWrapper* weights) {
    this->weights = weights;
}

int ConvolutionLayer::getNumGroups() const {
    return numGroups;
}


