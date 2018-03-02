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


#include <map>
#include <vector>

#include <ComputationHost.h>
#include <NetInfo.h>
#include <json.hpp>

using json = nlohmann::json;

/**
 * Provides a static method to distribute the images to different ComputationHosts. Can not be instantiated.
 */
class HostPlacer {

public:
    /**
     * This struct wraps up the performance of a computation host. Note that the powerConsumption is specified in watts.
     */
    struct Performance {
        int powerConsumption;
        int timeConsumption;

        Performance(int p, int t);
    };

private:
    static std::vector<std::pair<ComputationHost*, int>>& placeLowPower(
            std::vector<std::pair<ComputationHost*, Performance>> &hosts, int numOfImg);
    static std::vector<std::pair<ComputationHost*, int>>& placeHighPower(
            std::vector<std::pair<ComputationHost*, Performance>> &hosts, int numOfImg);
    static std::vector<std::pair<ComputationHost*, int>>& placeEnergyEfficient(
            std::vector<std::pair<ComputationHost*, Performance>> &hosts, int numOfImg);

    static const int timePriority = 1;
    static const int powerPriority = 1;
public:
    /**
     * Computes a distribution of tasks for the given ComputationHosts.
     * @param hosts     available computation hosts
     * @param net       neural net to use
     * @param numOfImg  number of images to classify
     * @param opMode    operation mode for the classification
     * @return          distribution of images, maps computation hosts to a number of images to classify
     */
    static std::vector<std::pair<ComputationHost*, int>>& place(std::vector<ComputationHost*> &hosts, int numOfImg,
    OperationMode opMode);


    /**
     * Reads the estimated performance of a ComputationHost.
     * @param c
     * @return pair of integers, containing power and time consumption.
     */
    static Performance readComputationHostInfo(std::string hostName);
};
