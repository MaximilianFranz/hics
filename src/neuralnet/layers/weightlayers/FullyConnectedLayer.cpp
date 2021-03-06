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

#include "FullyConnectedLayer.h"

FullyConnectedLayer::FullyConnectedLayer(std::vector<int> &inputDimensions, WeightWrapper *weights) {
    this->inputDimensions = inputDimensions;
    this->weights = weights;
    this->outputDimensions = calcOutputDimensions();
    this->type = LayerType::FULLYCONNECTED;
}

// Takes the outputDimensions based on the dimensions of the weights.
std::vector<int> FullyConnectedLayer::calcOutputDimensions() {
    std::vector<int> dim = {weights->getDimensions()[0]};
    return dim;
}

void FullyConnectedLayer::forward() {
    if (inputDimensions.size() == 3) {
        //stretch out the tf way
        DataWrapper *stretchedInput = stretchInput(previousLayer->getOutputWrapper());

        outputWrapper = new DataWrapper(getOutputDimensions());
        this->function->execute(*stretchedInput, *outputWrapper, *weights);

    }
    else {
        outputWrapper = new DataWrapper(getOutputDimensions());

        this->function->execute(*previousLayer->getOutputWrapper(), *outputWrapper, *weights);

        computed = true;
    }
}

// The computation neccessary for W*x = c where W ist the weights matrix and x the input vector
// are equal to the size of the matrix
int FullyConnectedLayer::getDifficulty() {
    if (this->difficulty == 0) {
        this-> difficulty = weights->getNumElements();
    }
    return this->difficulty;
}

// HELPER methods

DataWrapper *FullyConnectedLayer::stretchInput(DataWrapper *input) {
    int channels =  input->getDimensions().at(D3_Z_DIM);
    int y =  input->getDimensions().at(D3_Y_DIM);
    int x =  input->getDimensions().at(D3_X_DIM);
    int numElements = static_cast<int>(input->getNumElements()); //Input to FC are small

    float *inputData = previousLayer->getOutputWrapper()->getDataArray();
    std::vector<float> strechtedInputData(numElements);

    int i = 0;
    // Iterate over x and y from left to right and bottom to top.
    for (int yit = y - 1; yit >= 0; yit--) {
        for (int xit = x - 1; xit >= 0; xit--) {
            // Iterate over channels from front to back
            for (int cit = 0 ; cit < channels; cit++) {
                strechtedInputData[i] = inputData[cit*x*y + yit*x + xit];
 //               strechtedInputData[i] = input->getElement({cit, yit, xit});
                i++;
            }
        }
    }

    DataWrapper *stretchInput = new DataWrapper({numElements}, strechtedInputData);
    return stretchInput;
}

// SETTER methods

void FullyConnectedLayer::setPlatform(Platform *platform) {
    this->function = platform->createFullyConnectedFunction();
    this->functionSet = true;
}

