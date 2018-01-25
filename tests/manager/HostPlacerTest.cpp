//
// Created by jallmenroeder on 23/01/18.
//

#include "HostPlacerTest.h"

SCENARIO("Read values from JSON") {
    HostPlacer placer = HostPlacer();

    ComputationHost* localHost = new Executor("local");
    ComputationHost* fpgaHost = new Executor("fpga");

    REQUIRE(localHost->getName() == "local");

    HostPlacer::Performance localPerformance = HostPlacer::readComputationHostInfo(*localHost);
    HostPlacer::Performance fpgaPerformance = HostPlacer::readComputationHostInfo(*fpgaHost);

    REQUIRE(localPerformance.powerConsumption == 1500);
    REQUIRE(localPerformance.timeConsumption == 500);

    REQUIRE(fpgaPerformance.powerConsumption == 500);
    REQUIRE(fpgaPerformance.timeConsumption == 1500);
}
