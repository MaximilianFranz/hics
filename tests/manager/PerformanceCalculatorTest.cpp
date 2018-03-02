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

#include <PlatformInfo.h>
#include <PerformanceCalculator.h>
#include "PerformanceCalculatorTest.h"

SCENARIO("Test PerformanceCalculator") {
    PlatformInfo localCPU = PlatformInfo("Internal CPU", PlatformType::CPU, "cpu", 500, 1000);
    PlatformInfo localGPU = PlatformInfo("Internal GPU", PlatformType::GPU, "gpu", 2000, 4000);
    PlatformInfo fpga = PlatformInfo("Remote FPGA", PlatformType::FPGA, "fpga", 200, 1000);

    std::vector<std::pair<PlatformInfo*, float>> cpuDist;
    cpuDist.emplace_back(std::pair<PlatformInfo*, float>(&localCPU, 0.2f));
    cpuDist.emplace_back(std::pair<PlatformInfo*, float>(&localGPU, 0.8f));

    std::vector<std::pair<PlatformInfo*, float>> fpgaDist;
    fpgaDist.emplace_back(std::pair<PlatformInfo*, float>(&fpga, 1.0f));

    PerformanceCalculator::HostInfo localHost = PerformanceCalculator::HostInfo("local", 0.6f, 2000);
    PerformanceCalculator::HostInfo fpgaHost = PerformanceCalculator::HostInfo("fpga", 0.4f, 5000);

    SECTION("Test with two compHosts") {
        std::vector<std::vector<std::pair<PlatformInfo*, float>>> platformDist = {cpuDist, fpgaDist};
        std::vector<PerformanceCalculator::HostInfo*> hostDist = {&localHost, &fpgaHost};

        PerformanceData data = PerformanceCalculator::calculatePerformance(platformDist, hostDist);

        REQUIRE(data.getPlatformUsage()[0].first->getDescription() == "Internal CPU");
        REQUIRE(data.getPlatformUsage()[1].first->getDescription() == "Internal GPU");
        REQUIRE(data.getPlatformUsage()[2].first->getDescription() == "Remote FPGA");

        REQUIRE(data.getComputationTime() == 5000);

        int powerConsumptionValue = int(24952.0f * 2000.0f + 615.0f * 5000.0f) / 1000;
        REQUIRE(data.getPowerConsumption() == powerConsumptionValue);

    }
}
