/* Copyright 2018 The HICS Authors
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall
 * be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 */

#include "HostPlacerTest.h"

SCENARIO("Read values from JSON") {

    ComputationHost* localHost = new Executor("local");
    ComputationHost* fpgaHost = new Executor("fpga");
    ComputationHost *gpuHost = new Executor("GPU");

    REQUIRE(localHost->getName() == "local");

    SECTION("Test JSON reader") {
        HostPlacer::Performance localPerformance = HostPlacer::readComputationHostInfo(localHost->getName());
        HostPlacer::Performance fpgaPerformance = HostPlacer::readComputationHostInfo(fpgaHost->getName());

        REQUIRE(localPerformance.powerConsumption == 24952*150);
        REQUIRE(localPerformance.timeConsumption == 150);

        REQUIRE(fpgaPerformance.powerConsumption == 615*10974);
        REQUIRE(fpgaPerformance.timeConsumption == 10974);
    }

    SECTION("Test placeLowPower") {
        std::vector<ComputationHost*> hosts;
        hosts.push_back(localHost);
        hosts.push_back(fpgaHost);

        std::vector<std::pair<ComputationHost *, int >> distribution =
                HostPlacer::place(hosts, 5, OperationMode::LowPower);
        REQUIRE(distribution.size() == 2);
        REQUIRE(distribution.begin().operator*().first->getName() == "local");
        REQUIRE(distribution.begin().operator*().second == 5);
        REQUIRE((distribution.begin()+1).operator*().first->getName() == "fpga");
        REQUIRE((distribution.begin()+1).operator*().second == 0);
    }

    SECTION("Test placeLowPower with hosts with equal power consumption") {
        std::vector<ComputationHost*> hosts;
        ComputationHost* test = new Executor("test");
        hosts.push_back(localHost);
        hosts.push_back(fpgaHost);
        hosts.push_back(test);


        auto distribution = HostPlacer::place(hosts, 11, OperationMode::LowPower);
        REQUIRE(distribution.size() == 3);
        REQUIRE(distribution.begin().operator*().first->getName() == "local");
        REQUIRE(distribution.begin().operator*().second == 6);
        REQUIRE((distribution.begin()+1).operator*().first->getName() == "fpga");
        REQUIRE((distribution.begin()+1).operator*().second == 0);
        REQUIRE((distribution.begin()+2).operator*().first->getName() == "test");
        REQUIRE((distribution.begin()+2).operator*().second == 5);
    }

    SECTION("Test placeHighPower with two hosts") {
        std::vector<ComputationHost *> hosts;
        hosts.push_back(localHost);
        hosts.push_back(fpgaHost);

        std::vector<std::pair<ComputationHost *, int >> distribution =
                HostPlacer::place(hosts, 74, OperationMode::HighPower);
        REQUIRE(distribution.size() == 2);
        REQUIRE(distribution.begin().operator*().first->getName() == "local");
        REQUIRE(distribution.begin().operator*().second == 73);
        REQUIRE((distribution.begin() + 1).operator*().first->getName() == "fpga");
        REQUIRE((distribution.begin() + 1).operator*().second == 1);
    }

    SECTION("Test placeHighPower with three hosts") {
        std::vector<ComputationHost *> hosts;
        hosts.push_back(localHost);
        hosts.push_back(fpgaHost);
        hosts.push_back(gpuHost);

        std::vector<std::pair<ComputationHost *, int>> distribution =
                HostPlacer::place(hosts, 5, OperationMode::HighPower);
        REQUIRE(distribution.size() == 3);
        REQUIRE(distribution.begin().operator*().first->getName() == "local");
        REQUIRE(distribution.begin().operator*().second == 3);
        REQUIRE((distribution.begin() + 1).operator*().first->getName() == "fpga");
        REQUIRE((distribution.begin() + 1).operator*().second == 0);
        REQUIRE((distribution.begin() + 2).operator*().first->getName() == "GPU");
        REQUIRE((distribution.begin() + 2).operator*().second == 2);
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
        REQUIRE(distribution.begin().operator*().second == 4);
        REQUIRE((distribution.begin() + 1).operator*().first->getName() == "fpga");
        REQUIRE((distribution.begin() + 1).operator*().second == 0);
        REQUIRE((distribution.begin() + 2).operator*().first->getName() == "GPU");
        REQUIRE((distribution.begin() + 2).operator*().second == 0);
    }

}
