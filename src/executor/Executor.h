/* Copyright 2018 The HICS Authors
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall
 * be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 */

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
     * @param net                   a NetInfo specifying the net to setup.
     * @param mode                  OperationMode enum specifying the mode which to consider
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
     * @param data                  input data in a Wrapper.
     */
    void runDataForward(DataWrapper *data);

    /**
    * helper method returning the DataWrapper out of an ImageWrapper.
    *
    * Image information is lost at this point.
    *
    * @param imageWrapper          Wrapper containing the image data and meta information
    * @return
    */
    DataWrapper *getImageData(ImageWrapper *imageWrapper);

    NetInfo createMockInfo();

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
     * @param images                the images to be classified in ImageWrappers
     * @param net                   a NetInfo specifying which net ought to be used to classfiy
     * @param mode                  ENUM specifying which mode has been chosen
     * @param selectedPlatforms     list of PlatformInfo specifying which platforms to use for computation
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

    Executor(std::string name);

    std::string getName() {
        return name;
    }
};
