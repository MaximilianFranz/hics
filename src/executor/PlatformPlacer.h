//
// Created by Maximilian Franz on 08.01.18.
//

#pragma once


#include <vector>
#include <platforms/CpuPlatform.h>
#include "../neuralnet/NeuralNet.h"
#include "../manager/OperationMode.h"
#include "../platform/PlatformInfo.h"
#include "../platform/PlatformManager.h"
#include "Executor.h"

class PlatformPlacer {
private:
    OperationMode currentMode;          //! The OperationMode applied to the last configuration
    std::vector<PlatformInfo*> currentPlatformsInfos; //! The selected platforms infos in the last configurations
    std::vector<Platform*> currentPlatforms;  //! The corresponding platforms used in the last configuration

    PlatformManager* platformManager;   //! The platformManager is the access point to get available platforms
    NeuralNet *net;                     //! the net that has been configured in the last excectuion

    /**
     * Configures all Layers in the NeuralNet with default functions from CpuPlatform
     *
     * @param pLayer
     */
    void default_setLayerFunctionForLayer(Layer *pLayer);

    /**
     *
     * @return the CPU Platform for testing purposes
     */
    Platform * getDefaultPlatform();
public:
    /**
     * Default constructor ensuring that required dependencies are initialized.
     */
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
    void placeComputations(NeuralNet* net, OperationMode mode, std::vector<PlatformInfo*> platformInfos);

    /**
     * \brief returns PlatformInfo for all Platforms currently available
     *
     * Is called from Executor to pass available Platforms
     *
     * @return PlatformInfo of all Platforms the PlatformManager currently maintains
     */
    std::vector<PlatformInfo* > queryPlatforms();

};
