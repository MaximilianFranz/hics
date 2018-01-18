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
    throw NotImplementedException();
}

void Executor::setupIfChanged(NeuralNet *net, OperationMode mode, std::vector<PlatformInfo *> selectedPlatforms) {
    throw NotImplementedException();
}


