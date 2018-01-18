//
// Created by Maximilian Franz on 08.01.18.
//

#pragma once

//Use long relative path versions for now
#include <PlatformInfo.h>
#include <NetInfo.h>
#include <OperationMode.h>
#include "ImageResult.h"

/**
 * Defines the ComputationHost interface
 */
class ComputationHost {
public:
    // Must have pure virtual methods
    /**
     * Classifies the given images with the specified neural net, operation mode and selected Platforms.
     *
     * selectedPlatforms must be a subset of queryPlatforms() results.
     *
     * @param images
     * @param net
     * @param mode
     * @param selectedPlatforms
     * @return
     */
    virtual std::vector<ImageResult*> classify(std::vector<ImageWrapper*> images, NetInfo net, OperationMode mode,
                                              std::vector<PlatformInfo*> selectedPlatforms) = 0;
    /**
     * Queries the platforms available to this ComputationHost implementation.
     *
     * @return a list of PlatformInfo of the available Platform.
     */
    virtual std::vector<PlatformInfo*> queryPlatform() = 0;

    /**
     * Queries the neuralnet models available to this ComputationHost implementation
     *
     *
     * @return a list of NetInfo of the available NeuralNets.
     */
    virtual std::vector<NetInfo*> queryNets() = 0;


};
