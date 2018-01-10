//
// Created by jallmenroeder on 07/01/18.
//

#pragma once


#include <map>
#include <vector>

#include <ComputationHost.h>
#include <NetInfo.h>


class HostPlacer {
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
