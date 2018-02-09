//
// Created by Maximilian Franz on 07.01.18.
//

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


