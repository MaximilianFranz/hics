//
// Created by jallmenroeder on 27/01/18.
//

#include <PlatformInfo.h>
#include <PerformanceCalculator.h>
#include "PerformanceCalculatorTest.h"

SCENARIO("Test PerformanceCalculator") {
    PlatformInfo localCPU = PlatformInfo("Internal CPU", PlatformType::CPU, "cpu", 500, 1000);
    PlatformInfo localGPU = PlatformInfo("Internal GPU", PlatformType::GPU, "gpu", 2000, 4000);
    PlatformInfo fpga = PlatformInfo("Remote FPGA", PlatformType::FPGA, "fpga", 200, 1000);

    std::vector<std::pair<PlatformInfo, float>> cpuDist;
    cpuDist.emplace_back(std::pair<PlatformInfo, float>(localCPU, 0.2f));
    cpuDist.emplace_back(std::pair<PlatformInfo, float>(localGPU, 0.8f));

    std::vector<std::pair<PlatformInfo, float>> fpgaDist;
    fpgaDist.emplace_back(std::pair<PlatformInfo, float>(fpga, 1.0f));

    PerformanceCalculator::HostInfo localHost = PerformanceCalculator::HostInfo("local", 0.6f, 2000);
    PerformanceCalculator::HostInfo fpgaHost = PerformanceCalculator::HostInfo("fpga", 0.4f, 5000);

    SECTION("Test with two compHosts") {
        std::vector<std::vector<std::pair<PlatformInfo, float>>> platformDist = {cpuDist, fpgaDist};
        std::vector<PerformanceCalculator::HostInfo> hostDist = {localHost, fpgaHost};

        PerformanceData data = PerformanceCalculator::calculatePerformance(platformDist, hostDist);

        REQUIRE(data.getPlatformUsage()[0].first.getDescription() == "Internal CPU");
        REQUIRE(data.getPlatformUsage()[1].first.getDescription() == "Internal GPU");
        REQUIRE(data.getPlatformUsage()[2].first.getDescription() == "Remote FPGA");

        REQUIRE(data.getComputationTime() == 5000);

        int powerConsumptionValue = int((1500.0f / 500.0f) * 2000.0f + (500.0f / 1400.0f) * 5000.0f);
        REQUIRE(data.getPowerConsumption() == powerConsumptionValue);

    }
}
