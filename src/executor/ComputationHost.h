//
// Created by Maximilian Franz on 08.01.18.
//

#ifndef HICS_COMPUTATIONHOST_H
#define HICS_COMPUTATIONHOST_H

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
    //TODO: Documentation for ComputationHost
    /**
     *
     * @param images
     * @param net
     * @param mode
     * @param selectedPlatforms
     * @return
     */
    virtual std::vector<ImageResult> classify(std::vector<ImageWrapper> images, NetInfo net, OperationMode mode,
                                              std::vector<PlatformInfo> selectedPlatforms) = 0;
    /**
     *
     * @return
     */
    virtual std::vector<PlatformInfo> queryPlatform() = 0;

    /**
     *
     * @return
     */
    virtual std::vector<NetInfo> queryNets() = 0;


};


#endif //HICS_COMPUTATIONHOST_H
