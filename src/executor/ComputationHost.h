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

//Use long relative path versions for now
#include <PlatformInfo.h>
#include <NetInfo.h>
#include <OperationMode.h>
#include "ImageResult.h"

/**
 * Defines the ComputationHost interface
 */
class ComputationHost {
protected:
    std::string name;
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

    virtual ~ComputationHost() {

    }

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

    /**
     * Getter for name
     * @return name of the platform
     */
    virtual std::string getName() {
        return name;
    }

};
