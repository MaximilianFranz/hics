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
    throw NotImplementedException();
}

std::vector<NetInfo*> Executor::queryNets() {
    throw NotImplementedException();
}

void Executor::setup() {
    throw NotImplementedException();

}

ImageResult Executor::classifyImage() {
    throw NotImplementedException();
}


