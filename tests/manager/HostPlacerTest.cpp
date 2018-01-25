//
// Created by jallmenroeder on 23/01/18.
//

#include "HostPlacerTest.h"

SCENARIO("Read values from JSON") {

    ComputationHost* localHost = new Executor("local");
    ComputationHost* fpgaHost = new Executor("fpga");
    ComputationHost *gpuHost = new Executor("GPU");

    REQUIRE(localHost->getName() == "local");

    SECTION("Test JSON reader") {
        HostPlacer::Performance localPerformance = HostPlacer::readComputationHostInfo(*localHost);
        HostPlacer::Performance fpgaPerformance = HostPlacer::readComputationHostInfo(*fpgaHost);

        REQUIRE(localPerformance.powerConsumption == 1500);
        REQUIRE(localPerformance.timeConsumption == 500);

        REQUIRE(fpgaPerformance.powerConsumption == 500);
        REQUIRE(fpgaPerformance.timeConsumption == 1400);
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

    SECTION("Test placeHighPower with two hosts") {
        std::vector<ComputationHost *> hosts;
        hosts.push_back(localHost);
        hosts.push_back(fpgaHost);

        std::vector<std::pair<ComputationHost *, int >> distribution =
                HostPlacer::place(hosts, 5, OperationMode::HighPower);
        REQUIRE(distribution.size() == 2);
        REQUIRE(distribution.begin().operator*().first->getName() == "local");
        REQUIRE(distribution.begin().operator*().second == 4);
        REQUIRE((distribution.begin() + 1).operator*().first->getName() == "fpga");
        REQUIRE((distribution.begin() + 1).operator*().second == 1);
    }

    SECTION("Test placeHighPower with three hosts") {
        std::vector<ComputationHost *> hosts;
        hosts.push_back(localHost);
        hosts.push_back(fpgaHost);
        hosts.push_back(gpuHost);

        std::vector<std::pair<ComputationHost *, int>> distribution =
                HostPlacer::place(hosts, 10, OperationMode::HighPower);
        REQUIRE(distribution.size() == 3);
        REQUIRE(distribution.begin().operator*().first->getName() == "local");
        REQUIRE(distribution.begin().operator*().second == 3);
        REQUIRE((distribution.begin() + 1).operator*().first->getName() == "fpga");
        REQUIRE((distribution.begin() + 1).operator*().second == 1);
        REQUIRE((distribution.begin() + 2).operator*().first->getName() == "GPU");
        REQUIRE((distribution.begin() + 2).operator*().second == 6);
    }

    SECTION("Test placeEnergyEfficient with 4 images") {
        std::vector<ComputationHost *> hosts;
        hosts.push_back(localHost);
        hosts.push_back(fpgaHost);
        hosts.push_back(gpuHost);

        std::vector<std::pair<ComputationHost *, int>> distribution =
                HostPlacer::place(hosts, 4, OperationMode::EnergyEfficient);
        REQUIRE(distribution.size() == 3);
        REQUIRE(distribution.begin().operator*().first->getName() == "local");
        REQUIRE(distribution.begin().operator*().second == 1);
        REQUIRE((distribution.begin() + 1).operator*().first->getName() == "fpga");
        REQUIRE((distribution.begin() + 1).operator*().second == 1);
        REQUIRE((distribution.begin() + 2).operator*().first->getName() == "GPU");
        REQUIRE((distribution.begin() + 2).operator*().second == 2);

    }

}
