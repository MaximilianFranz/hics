//
// Created by Maximilian Franz on 08.01.18.
//

#pragma once

#include <vector>
#include <NeuralNet.h>
#include <NetBuilder.h>
#include <SimpleNetIterator.h>

#include "ImageResult.h"
#include "ComputationHost.h"
#include "PlatformPlacer.h"
#include "Interpreter.h"

class PlatformPlacer;

class Executor : public ComputationHost {
private:
    NeuralNet *net;
    OperationMode currentMode;
    std::vector<PlatformInfo*> currentPlatforms;

    NetBuilder *builder;
    PlatformPlacer *placer;
    Interpreter *interpreter;
    std::string name;



    /**
     * Ensures that required settings are met and satisfies missing settings by building or configuring them.
     *
     * This changes NeuralNet or Placement iff they have changed since the last call to this method!
     *
     * @param net
     * @param mode
     * @param selectedPlatforms
     */
    void setupIfChanged(NetInfo *net, OperationMode mode, std::vector<PlatformInfo*> &selectedPlatforms);

    /**
     * Classfies a single image with the settings currently set for this Executor.
     *
     * @return a single ImageResult
     */
    ImageResult *classifyImage(ImageWrapper* image);

    /**
     * Propagates the given data through the network and handles garbage collection of unused DataWrapperss
     *
     * @param image
     */
    void runDataForward(DataWrapper *data);

public:

    /**
     * Default constructor ensuring that PlatformPlacer and NetBuilder are available
     *
     */
    Executor();

    /**
     * Classifies the given images with the requested settings (mode, net, platforms)
     *
     * This method hides the core functionality of our system and dispatches the different requirements to
     * the corresponding modules and classes.
     *
     * @param images the images to be classified in ImageWrappers
     * @param net a NetInfo specifying which net ought to be used to classfiy
     * @param mode ENUM specifying which mode has been chosen
     * @param selectedPlatforms list of PlatformInfo specifying which platforms to use for computation
     * @return list of classfied Images with the top-5 results in an ImageResult!
     */
    std::vector<ImageResult*> classify(std::vector<ImageWrapper*> images, NetInfo net, OperationMode mode,
                                      std::vector<PlatformInfo*> selectedPlatforms) override;

    /**
     * Queries available platforms by passing the query to the PlatformPlacer
     *
     * @return list fo PlatformInfo of Platforms available to the PlatformManager
     */
    std::vector<PlatformInfo*> queryPlatform() override;

    /**
     * Queries available neural net models by passing the query on to the NetBuilder.
     *
     * @return list of NetInfo of the available neural net models.
     */
    std::vector<NetInfo*> queryNets() override;

    DataWrapper *getImageData(ImageWrapper *imageWrapper);

    Executor(std::string name) : name(name){};

    std::string getName() {
        return name;
    }
};
