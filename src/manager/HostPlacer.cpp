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

#include <iostream>
#include <fstream>
#include <ResourceException.h>

#include "HostPlacer.h"


HostPlacer::Performance HostPlacer::readComputationHostInfo(std::string hostName) {
    std::ifstream i(RES_DIR "computationHosts.json");
    json computationHostFile;
    i >> computationHostFile;
    json computationHost = computationHostFile["computationHosts"];

    for (auto compHostIt : computationHost) {
        if (compHostIt["name"] == hostName) {
            int power = compHostIt["power"];
            int time = compHostIt["time"];
            //multiply power with time to get the power consumption per classification
            power = power * time;
            return {power, time};
        }
    }
    throw ResourceException("computation host not found in " RES_DIR "computationHosts.json");
}

std::vector<std::pair<ComputationHost*, int>>&
HostPlacer::place(std::vector<ComputationHost*> &hosts, int numOfImg, OperationMode opMode) {

    std::vector<std::pair<ComputationHost*, Performance>> hostPerformance;

    //Read performance of every host from JSON
    for (auto host : hosts) {
        Performance temp = readComputationHostInfo(host->getName());
        hostPerformance.emplace_back(std::pair<ComputationHost *, HostPlacer::Performance>(host, temp));
    }

    //Select algorithm to calculate distribution according to operation mode
    switch (opMode) {
        case EnergyEfficient :
            return placeEnergyEfficient(hostPerformance, numOfImg);
        case LowPower :
            return placeLowPower(hostPerformance, numOfImg);
        case HighPower :
            return placeHighPower(hostPerformance, numOfImg);
        default:
            throw IllegalArgumentException("No such OperationMode");
    }
}

//TODO: Case: Two or more Hosts have the least amaount of power usage
std::vector<std::pair<ComputationHost *, int>> &
HostPlacer::placeLowPower(std::vector<std::pair<ComputationHost *, HostPlacer::Performance>> &hosts, int numOfImg) {
    //Find the Host with the least power consumption
    auto lowest = std::min_element(hosts.begin(), hosts.end(),
                                        [] (std::pair<ComputationHost *, HostPlacer::Performance> &left,
                                            std::pair<ComputationHost *, HostPlacer::Performance> &right) {
                                            return left.second.powerConsumption < right.second.powerConsumption;
                                        });
    std::vector<ComputationHost*> allLowest;
    for (auto host : hosts) {
        if (host.second.powerConsumption == lowest.operator*().second.powerConsumption) {
            allLowest.push_back(host.first);
        }
    }
    int workload = int(numOfImg / allLowest.size());
    int remainder = int(numOfImg % allLowest.size());

    //Give him all images
    auto *distribution = new std::vector<std::pair<ComputationHost *, int>>();
    //(*distribution).emplace_back(std::pair<ComputationHost *, int>(lowest.operator*().first, numOfImg));
    for (auto hostIt : hosts) {
        if (std::find_if(allLowest.begin(), allLowest.end(), [&hostIt](ComputationHost* currentHost) {
            return hostIt.first->getName() == currentHost->getName();
        }) != allLowest.end()) {
            int hostload = workload;
            if (remainder > 0) {
                hostload++;
                remainder--;
            }
            distribution->emplace_back(hostIt.first, hostload);
        } else {
            distribution->emplace_back(hostIt.first, 0);
        }
    }
    return *distribution;
}


std::vector<std::pair<ComputationHost *, int>> &
HostPlacer::placeHighPower(std::vector<std::pair<ComputationHost *, HostPlacer::Performance>> &hosts, int numOfImg) {

    //init vector with jobStack for each host
    std::vector<int> jobStacks = std::vector<int>();
    auto distribution = new std::vector<std::pair<ComputationHost *, int>>;

    for (auto host : hosts) {
        jobStacks.push_back(0);
        distribution->emplace_back(host.first, 0);
    }

    for (int i = 0; i < numOfImg; i++) {
        int currentMin = INT32_MAX;
        ComputationHost *currentMinHost;
        int hostIndex = 0;
        int minHostIndex = -1;

        //Find the minimum jobStack for the next image
        for (auto currentHost : hosts) {
            int estimatedTime = jobStacks[hostIndex] + currentHost.second.timeConsumption;
            if (estimatedTime < currentMin) {
                currentMinHost = currentHost.first;
                currentMin = estimatedTime;
                minHostIndex = hostIndex;
            }

            hostIndex++;
        }
        jobStacks[minHostIndex] = currentMin;

        //add image to job List
        std::find_if(distribution->begin(), distribution->end(),
                     [&currentMinHost](std::pair<ComputationHost *, int> element) {
                         return element.first->getName() == currentMinHost->getName();
                     }).operator*().second++;
    }
    return *distribution;
}

std::vector<std::pair<ComputationHost *, int>> &
HostPlacer::placeEnergyEfficient(std::vector<std::pair<ComputationHost *, HostPlacer::Performance>> &hosts,
                                 int numOfImg) {

    //init vector with jobStack for each host
    std::vector<int> jobStacks = std::vector<int>();
    auto distribution = new std::vector<std::pair<ComputationHost *, int>>;

    for (auto host : hosts) {
        jobStacks.push_back(0);
        distribution->emplace_back(host.first, 0);
    }

    int currentTimeMax = 0;
    for (int i = 0; i < numOfImg; i++) {
        int currentTime = 0;
        int currentCostMin = INT32_MAX;
        int hostIndex = 0;
        int minHostIndex = -1;
        int newStackHeight = 0;
        ComputationHost *currentMinHost;

        //find image with the least cost coefficient for the next image
        //this takes in account the time and power consumption of the computation multiplied with power/time priority
        for (auto host : hosts) {
            currentTime = jobStacks[hostIndex] + host.second.timeConsumption;
            int currentCost = std::max((currentTime - currentTimeMax), 0) * timePriority +
                    host.second.powerConsumption * powerPriority;
            if (currentCost < currentCostMin) {
                currentCostMin = currentCost;
                minHostIndex = hostIndex;
                currentMinHost = host.first;
                newStackHeight = currentTime;
            }
            hostIndex++;
        }
        jobStacks[minHostIndex] = newStackHeight;
        currentTimeMax = std::max(currentTimeMax, jobStacks[minHostIndex]);

        //add image to job List
        std::find_if(distribution->begin(), distribution->end(),
                     [&currentMinHost](std::pair<ComputationHost *, int> element) {
                         return element.first->getName() == currentMinHost->getName();
                     }).operator*().second++;
    }

    return *distribution;
}


HostPlacer::Performance::Performance(int p, int t) : powerConsumption(p), timeConsumption (t) {
}
