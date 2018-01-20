//
// Created by Maximilian Franz on 07.01.18.
//

#include "ConvolutionLayer.h"
#include "NotImplementedException.h"

const int X_DIM = 2;
const int Y_DIM = 1;
const int Z_DIM = 0;



//TODO: Test this!
std::vector<int> ConvolutionLayer::calcOutputDimensions() {
    int outputWidth = ( (this->inputDimensions[D3_X_DIM] - filterSize) / stride) + 1;
    std::vector<int> outDim(3); // three dimensional output
    outDim[X_DIM] = outputWidth; // X, Y are the same!
    outDim[Y_DIM] = outputWidth;
    outDim[Z_DIM] = numFilters;

}


void ConvolutionLayer::setWeights(WeightWrapper* weights) {
    this->weights = weights;
}


bool ConvolutionLayer::verifyWeights() {
    return false;
}

ConvolutionLayer::ConvolutionLayer(int numFilters, int filterSize, int zeroPadding, int stride,
                                   std::vector<int> &inputDimensions)
        : numFilters(numFilters),
          filterSize(filterSize),
          zeroPadding(zeroPadding),
          stride(stride) {
    this->inputDimensions = inputDimensions;
    this->type = CONVOLUTION;
    this->outputDimensions = calcOutputDimensions();
    init(); // TODO never call virtual functions in constructor
}

ConvolutionLayer::ConvolutionLayer(int numFilters, int filterSize, int zeroPadding, int stride,
                                   std::vector<int> &inputDimensions, WeightWrapper *weights)
        : numFilters(numFilters),
          filterSize(filterSize),
          zeroPadding(zeroPadding),
          stride(stride),
          weights(weights)
{
    this->inputDimensions = inputDimensions;
    this->type = CONVOLUTION;
    this->outputDimensions = calcOutputDimensions();
    init(); // TODO never call virtual functions in constructor
}

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

void ConvolutionLayer::forward() {
    this->function->execute(*previousLayer->getOutputWrapper(), *outputWrapper, *weights, stride, filterSize, numFilters, zeroPadding);
    computed = true;
}


