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
#include <map>

#include "NeuralNet.h"
#include "NetInfo.h"


class NetBuilder {

public:

    /***
     * Constructs a neural net based on given net information.
     *
     * @param net net information
     *
     * @return a new NeuralNet object created from given NetInfo object
     */
    NeuralNet* buildNeuralNet(NetInfo net);

    /**
     * Provides a list of available net information objects.
     *
     * @return a vector with the pointers to netInfos of neural nets that can be built
     */
    std::vector<NetInfo*> queryAvailableNets();

    /**
     * Provides a list of classes objects on the image can be classified into.
     *
     * @param net net information
     *
     * @return a map with numbers from 1 to 1000 and classes that correspond to them
     */
    const std::map<int, std::string> getLabelMap(NetInfo *net);

    //Static path to the model directory.
    const std::string MODEL_DIR = RES_DIR "models";
};
