//
// Created by Maximilian Franz on 08.01.18.
//

#ifndef HICS_COMPUTATIONHOST_H
#define HICS_COMPUTATIONHOST_H

//Use long relative path versions for now
//TODO: Update to direct includes!
#include "../netbuilder/wrapper/ImageWrapper.h"
#include "ImageResult.h"
#include "../netbuilder/NetInfo.h"
#include "../manager/OperationMode.h"
#include "../platform/PlatformInfo.h"

/**
 * Defines the ComputationHost interface
 */
class ComputationHost {
public:
    // Must have pure virtual methods
    virtual std::vector<ImageResult> classify(std::vector<ImageWrapper> images, NetInfo net, OperationMode mode,
                                                std::vector<PlatformInfo> selectedPlatforms) = 0;
    virtual std::vector<PlatformInfo> queryPlatform() = 0;
    virtual std::vector<NetInfo> queryNets() = 0;


};


#endif //HICS_COMPUTATIONHOST_H
