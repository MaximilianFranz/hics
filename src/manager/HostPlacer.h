//
// Created by jallmenroeder on 07/01/18.
//

#pragma once


#include <map>
#include <vector>

#include <ComputationHost.h>
#include <NetInfo.h>
#include <json.hpp>
#include <loader/StringLoader.h>

using json = nlohmann::json;

/**
 * Provides a static method to distribute the images to different ComputationHosts. Can not be instantiated.
 */
class HostPlacer {

public:
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

    static const int timePriority = 2;
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
    static Performance readComputationHostInfo(ComputationHost& c);
};
