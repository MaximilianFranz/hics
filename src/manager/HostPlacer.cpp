//
// Created by jallmenroeder on 07/01/18.
//

#include <iostream>
#include "HostPlacer.h"

bool jsonComparator(const json& first, const json& second) {
    first["name"] == second["name"];
}


HostPlacer::Performance HostPlacer::readComputationHostInfo(ComputationHost& c) {
    std::string jsonStr = StringLoader::getStringFromFile("../../../src/manager/computationHosts.json");
    json computationHostFile = json::parse(jsonStr);
    json computationHost = computationHostFile["computationHosts"];

    for (auto compHostIt : computationHost) {
        if (compHostIt["name"] == c.getName()) {
            int power = compHostIt["power"];
            int time = compHostIt["time"];
            return Performance(power, time);
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
        Performance temp = readComputationHostInfo(*host);
        hostPerformance.emplace_back(host, temp);
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

std::vector<std::pair<ComputationHost *, int>> &
HostPlacer::placeLowPower(std::vector<std::pair<ComputationHost *, HostPlacer::Performance>> &hosts, int numOfImg) {
    //Find the Host with the least power consumption
    auto lowest = std::min_element(hosts.begin(), hosts.end(),
                                        [] (std::pair<ComputationHost *, HostPlacer::Performance> &left,
                                            std::pair<ComputationHost *, HostPlacer::Performance> &right) {
                                            return left.second.powerConsumption < right.second.powerConsumption;
                                        });
    //Give him all images
    std::vector<std::pair<ComputationHost *, int>> distribution;
    distribution.emplace_back(lowest.operator*().first, numOfImg);
    for (auto hostIt : hosts) {
        if (hostIt.first != lowest.operator*().first) {
            distribution.emplace_back(hostIt.first, 0);
        }
    }
}

std::vector<std::pair<ComputationHost *, int>> &
HostPlacer::placeHighPower(std::vector<std::pair<ComputationHost *, HostPlacer::Performance>> &hosts, int numOfImg) {
    //return <#initializer#>;
}

std::vector<std::pair<ComputationHost *, int>> &
HostPlacer::placeEnergyEfficient(std::vector<std::pair<ComputationHost *, HostPlacer::Performance>> &hosts,
                                 int numOfImg) {
    //return <#initializer#>;
}


HostPlacer::Performance::Performance(int p, int t) : powerConsumption(p), timeConsumption (t) {
}
