//
// Created by Maximilian Franz on 08.01.18.
//

#pragma once

#include <vector>
#include <NeuralNet.h>
#include <NetBuilder.h>
#include "ImageResult.h"

#include "ComputationHost.h"
#include "PlatformPlacer.h"

class PlatformPlacer;

class Executor : ComputationHost{
private:
    NeuralNet *net;
    NetBuilder *builder;
    PlatformPlacer* placer;
    OperationMode currentMode;
    std::vector<PlatformInfo*> currentPlatforms;

    void setup();
    ImageResult classifyImage();

public:
    // TODO: Implement constructors and dependency relation to PlatformPlacer -> PlatformManager, etc...
    Executor();

    std::vector<ImageResult*> classify(std::vector<ImageWrapper*> images, NetInfo net, OperationMode mode,
                                      std::vector<PlatformInfo*> selectedPlatforms) override;

    std::vector<PlatformInfo*> queryPlatform() override;

    std::vector<NetInfo*> queryNets() override;

};
