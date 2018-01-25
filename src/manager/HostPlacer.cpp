//
// Created by jallmenroeder on 07/01/18.
//

#include <iostream>
#include "HostPlacer.h"

bool jsonComparator(const json& first, const json& second) {
    first["name"] == second["name"];
}


HostPlacer::Performance HostPlacer::readComputationHostInfo(ComputationHost &c) {
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

HostPlacer::Performance::Performance(int p, int t) : powerConsumption(p), timeConsumption (t) {
}
