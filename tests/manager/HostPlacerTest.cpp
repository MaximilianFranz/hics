//
// Created by jallmenroeder on 23/01/18.
//

#include "HostPlacerTest.h"

SCENARIO("Read values from JSON") {

    ComputationHost* localHost = new Executor("local");
    ComputationHost* fpgaHost = new Executor("fpga");

    REQUIRE(localHost->getName() == "local");

    SECTION("Test JSON reader") {
        HostPlacer::Performance localPerformance = HostPlacer::readComputationHostInfo(*localHost);
        HostPlacer::Performance fpgaPerformance = HostPlacer::readComputationHostInfo(*fpgaHost);

        REQUIRE(localPerformance.powerConsumption == 1500);
        REQUIRE(localPerformance.timeConsumption == 500);

        REQUIRE(fpgaPerformance.powerConsumption == 500);
        REQUIRE(fpgaPerformance.timeConsumption == 1500);
    }

    SECTION("Test placeLowPower") {
        std::vector<ComputationHost*> hosts;
        hosts.push_back(localHost);
        hosts.push_back(fpgaHost);

        std::vector<std::pair<ComputationHost *, int >> distribution =
                HostPlacer::place(hosts, 5, OperationMode::LowPower);
        REQUIRE(distribution.size() == 2);
        REQUIRE(distribution.begin().operator*().first->getName() == "fpga");
        REQUIRE(distribution.begin().operator*().second == 5);
        REQUIRE((distribution.begin()+1).operator*().first->getName() == "local");
        REQUIRE((distribution.begin()+1).operator*().second == 0);
    }
}
