//
// Created by jallmenroeder on 07/01/18.
//

#include <iostream>
#include <fstream>
#include "HostPlacer.h"


HostPlacer::Performance HostPlacer::readComputationHostInfo(std::string hostName) {
    std::ifstream jsonFile(RES_DIR "computationHosts.json");
    std::ostringstream tmp;
    tmp<<jsonFile.rdbuf();
    std::string jsonStr = tmp.str();
    json computationHostFile = json::parse(jsonStr);
    json computationHost = computationHostFile["computationHosts"];

    for (auto compHostIt : computationHost) {
        if (compHostIt["name"] == hostName) {
            int power = compHostIt["power"];
            int time = compHostIt["time"];
            return {power, time};
        }
    }
    //TODO: real execption
    throw std::exception();
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
            //TODO: real exception
            throw std::exception();
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
    //Give him all images
    auto *distribution = new std::vector<std::pair<ComputationHost *, int>>();
    //(*distribution).emplace_back(std::pair<ComputationHost *, int>(lowest.operator*().first, numOfImg));
    for (auto hostIt : hosts) {
        if (hostIt.first->getName() == lowest.operator*().first->getName()) {
            (*distribution).emplace_back(lowest.operator*().first, numOfImg);
        } else {
            (*distribution).emplace_back(hostIt.first, 0);
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
