//
// Created by Maximilian Franz on 08.01.18.
//

#include <NotImplementedException.h>
#include "Executor.h"

std::vector<ImageResult*> Executor::classify(std::vector<ImageWrapper*> images, NetInfo netinfo, OperationMode mode,
                                            std::vector<PlatformInfo*> selectedPlatforms) {
    setupIfChanged(&netinfo, mode, selectedPlatforms);
    auto labelMap = builder->getLabelMap(&netinfo);
    interpreter = new Interpreter(labelMap);
    std::vector<ImageResult*> results(Interpreter::TOP_X); //Number of Results from Interpreter settings

    for (auto image : images) {
        ImageResult *r = classifyImage(image);
        results.push_back(r);
    }

    return results;
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

ImageResult *Executor::classifyImage(ImageWrapper *image) {
    runDataForward(getImageData(image));
    auto outputData = net->getLastLayer()->getOutputWrapper();
    return interpreter->getResult(outputData, image);

}

void Executor::setupIfChanged(NetInfo *netInfo, OperationMode mode, std::vector<PlatformInfo *> &selectedPlatforms) {
    if(netInfo->getIdentifier() != this->net->getInfo().getIdentifier()) { //TODO: Overide == operator in NetInfo
        net = builder->buildNeuralNet(*netInfo);
    }
    if (currentMode != mode || selectedPlatforms != currentPlatforms) {
        placer->placeComputations(net, mode, selectedPlatforms);
    }
}

DataWrapper *Executor::getImageData(ImageWrapper *imageWrapper) {
    std::vector<float> imageData = imageWrapper->getData();
    return new DataWrapper(imageWrapper->getDimensions(), imageData);
}

void Executor::runDataForward(DataWrapper *data) {
    SimpleNetIterator* it = net->createIterator();
    it->getElement()->setInputWrapper(data); // SET INPUT TO FIRST LAYER EXPLICITLY!
    while (it->hasNext()) {
        it->getElement()->forward();
        it->getElement()->deleteGarbage();
        it->next();
    }

}


