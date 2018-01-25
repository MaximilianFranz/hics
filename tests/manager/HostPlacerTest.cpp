//
// Created by jallmenroeder on 23/01/18.
//

#include "HostPlacerTest.h"

struct Performance {
    int power;
    int time;

    Performance(int p, int t) : power(p), time(t) {};
};

SCENARIO("Read values from JSON") {
    HostPlacer placer = HostPlacer();

    ComputationHost* localHost = new Executor("local");
    ComputationHost* fpgaHost = new Executor("fpga");

    REQUIRE(localHost->getName() == "local");

    HostPlacer::Performance localPerformance = placer.readComputationHostInfo(*localHost);
    HostPlacer::Performance fpgaPerformance = placer.readComputationHostInfo(*fpgaHost);

    REQUIRE(localPerformance.powerConsumption == 1500);
    REQUIRE(localPerformance.timeConsumption == 500);

    REQUIRE(fpgaPerformance.powerConsumption == 500);
    REQUIRE(fpgaPerformance.timeConsumption == 1500);
}
