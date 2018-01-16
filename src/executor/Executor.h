//
// Created by Maximilian Franz on 08.01.18.
//

#pragma once

#include <vector>
#include <NeuralNet.h>
#include "ImageResult.h"

#include "ComputationHost.h"

class Executor : ComputationHost{
private:
    NeuralNet *net;
    OperationMode currentMode;
    std::vector<PlatformInfo*> currentPlatforms;

    void setup();
    ImageResult classifyImage();

public:
    std::vector<ImageResult*> classify(std::vector<ImageWrapper*> images, NetInfo net, OperationMode mode,
                                      std::vector<PlatformInfo*> selectedPlatforms) override;

    std::vector<PlatformInfo*> queryPlatform() override;

    std::vector<NetInfo*> queryNets() override;

};


