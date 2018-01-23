//
// Created by jallmenroeder on 07/01/18.
//

#pragma once


#include <map>
#include <vector>

#include <ComputationHost.h>
#include <NetInfo.h>
#include <loader/json.hpp>
#include <loader/StringLoader.h>

using json = nlohmann::json;

/**
 * Provides a static method to distribute the images to different ComputationHosts. Can not be instantiated.
 */
class HostPlacer {
    struct Performance {
        int powerConsumption;
        int timeConsumption;

        Performance(int p, int t);
    };

private:
    /**
     * Reads the estimated performance of a ComputationHost.
     * @param c
     * @return pair of integers, containing power and time consumption.
     */
    Performance readComputationHostInfo(ComputationHost c);
public:
    /**
     * Computes a distribution of tasks for the given ComputationHosts.
     * @param hosts     available computation hosts
     * @param net       neural net to use
     * @param numOfImg  number of images to classify
     * @param opMode    operation mode for the classification
     * @return          distribution of images, maps computation hosts to a number of images to classify
     */
    static std::map<ComputationHost, int> place(std::vector<ComputationHost> hosts, NetInfo net, int numOfImg,
    OperationMode opMode);
};
