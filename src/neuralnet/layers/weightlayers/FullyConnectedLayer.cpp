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

FullyConnectedLayer::FullyConnectedLayer(std::vector<int> inputDimensions) {
    this->inputDimensions = inputDimensions;
}

FullyConnectedLayer::FullyConnectedLayer(std::vector<int> inputDimensions, WeightWrapper *weights) {
    this->inputDimensions = inputDimensions;
    this->weights = weights;
    this->outputDimensions = calcOutputDimensions();
    this->type = FULLYCONNECTED;
}

//TODO: Verify. This should
std::vector<int> FullyConnectedLayer::calcOutputDimensions() {
    std::vector<int> dim = {weights->getDimensions()[0]}; //For some reason the convention does not hold here!
    return dim;
}

void FullyConnectedLayer::setWeights(WeightWrapper *weights) {
    this->weights = weights;
}


//TODO: Implement checks if the weights fit the layer!
bool FullyConnectedLayer::verifyWeights() {
    return false;
}

void FullyConnectedLayer::setFunction(FullyConnectedFunction *function) {
    this->function = function;
    functionSet = true;
}

void FullyConnectedLayer::forward() {
    if (inputDimensions.size() != 1) {
        //stretch out the tf way
        DataWrapper *input = previousLayer->getOutputWrapper();
        int channels =  input->getDimensions().at(D3_Z_DIM);
        int y =  input->getDimensions().at(D3_Y_DIM);
        int x =  input->getDimensions().at(D3_X_DIM);
        int numElements = static_cast<int>(input->getNumElements()); //Input to FC are small
        float *inputData = previousLayer->getOutputWrapper()->getDataArray();
        std::vector<float> strechtInputData(numElements);
        int i = 0;
        //TODO: Optimize perfomance of this!
        //Don't ask how I got to this solution.
        for (int yit = y-1; yit >= 0; yit--) {
            for (int xit = x - 1; xit >= 0; xit--) {
                for (int cit = 0 ; cit < channels; cit++) {
                    strechtInputData[i] = previousLayer->getOutputWrapper()->getElement({cit, yit, xit});
                    i++;
                }
            }
        }


        DataWrapper *stretchInput = new DataWrapper({numElements}, strechtInputData);
        outputWrapper = new DataWrapper(getOutputDimensions());
        this->function->execute(*stretchInput,*outputWrapper, *weights);

    }
    else {
        outputWrapper = new DataWrapper(getOutputDimensions());

        this->function->execute(*previousLayer->getOutputWrapper(), *outputWrapper, *weights);

        computed = true;
    }
}


