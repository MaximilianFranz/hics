//
// Created by Maximilian Franz on 08.01.18.
//

#include <NotImplementedException.h>
#include "Executor.h"

std::vector<ImageResult*> Executor::classify(std::vector<ImageWrapper*> images, NetInfo net, OperationMode mode,
                                            std::vector<PlatformInfo*> selectedPlatforms) {
    throw NotImplementedException();
}

std::vector<PlatformInfo*> Executor::queryPlatform() {
    return placer->queryPlatforms();
}

std::vector<NetInfo*> Executor::queryNets() {
    return builder->queryAvailableNets();
}


Executor::Executor() {
    this->placer = (new PlatformPlacer());
    this->builder = (new NetBuilder());

}

ImageResult Executor::classifyImage(ImageWrapper *image) {
    SimpleNetIterator* it = net->createIterator();
    std::vector<float> data = image->getData();
    DataWrapper inputData(it->getElement()->getInputDimensions(), data);
    DataWrapper outputData(it->getElement()->getOutputDimensions());
    while (it->hasNext()) {
        it->getElement()->forward(inputData, outputData);
        DataWrapper inputData = &outputData;

        it->next();
    }
}

void Executor::setupIfChanged(NeuralNet *net, OperationMode mode, std::vector<PlatformInfo *> selectedPlatforms) {
    throw NotImplementedException();
}


