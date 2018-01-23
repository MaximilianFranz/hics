//
// Created by jallmenroeder on 07/01/18.
//

#include "HostPlacer.h"

bool jsonComparator(const json& first, const json& second) {
    first["name"] == second["name"];
}


HostPlacer::Performance HostPlacer::readComputationHostInfo(ComputationHost c) {
    std::string jsonStr = StringLoader::getStringFromFile("computationHosts.json");
    json computationHosts = json::parse(jsonStr)[computationHosts];

    nlohmann::basic_json::iterator performanceIt =
            std::find(computationHosts.begin(), computationHosts.end(), jsonComparator);

    if (performanceIt != computationHosts.end()) {
        int power = performanceIt.operator*()["power"];
        int time = performanceIt.operator*()["time"];
        Performance performance = Performance(power, time);
        return performance;
    } else {
        //TODO: EXCEPTION
        throw std::exception();
    }
}

HostPlacer::Performance::Performance(int p, int t) : powerConsumption(p), timeConsumption (t) {
}
