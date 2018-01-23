//
// Created by jallmenroeder on 07/01/18.
//

#include "HostPlacer.h"

bool jsonComparator(const json& first, const json& second) {
    first["name"] == second["name"];
}


HostPlacer::Performance HostPlacer::readComputationHostInfo(ComputationHost &c) {
    std::string jsonStr = StringLoader::getStringFromFile("computationHosts.json");
    json computationHost = json::parse(jsonStr)["computationHosts"];

    for (json jsonIt : computationHost) {
        if (jsonIt["name"] == c.getName()) {
            int power = jsonIt["power"];
            int time = jsonIt["time"];
            return Performance(power, time);
        }
    }

    throw std::exception();
}

HostPlacer::Performance::Performance(int p, int t) : powerConsumption(p), timeConsumption (t) {
}
