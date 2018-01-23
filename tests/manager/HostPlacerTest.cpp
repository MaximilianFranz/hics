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

    HostPlacer::Performance localPerformance = placer.readComputationHostInfo(*localHost);
}
