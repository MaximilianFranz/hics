//
// Created by Maximilian Franz on 08.01.18.
//

#pragma once


#include <vector>
#include "../neuralnet/NeuralNet.h"
#include "../manager/OperationMode.h"
#include "../platform/PlatformInfo.h"
#include "../platform/PlatformManager.h"
#include "Executor.h"

class PlatformPlacer {
private:
    OperationMode currentMode;
    std::vector<PlatformInfo> currentPlatforms;
    PlatformManager* platformManager;
    NeuralNet *net;
public:
    PlatformPlacer();

    /**
     * \brief Distributes computation in the NeuralNet to Platforms according to selected OperationMode.
     *
     * Places the single layer computations to the selected platforms according to their performance
     * and power consumption. Placement is only performed iff (if and only if) settings have changed.
     *
     * @param net containing the Layers which are to be distributed
     * @param mode chosen OperationMode to consider during placement
     * @param platforms chosen platforms to place computations on
     */
    void placeComputations(NeuralNet* net, OperationMode mode, std::vector<PlatformInfo*> platforms);

    /**
     * \brief returns PlatformInfo for all Platforms currently available
     *
     * Is called from Executor to pass available Platforms
     *
     * @return PlatformInfo of all Platforms the PlatformManager currently maintains
     */
    std::vector<PlatformInfo* > queryPlatforms();

};
