//
// Created by jallmenroeder on 19/01/18.
//

#include "ClassificationResultTest.h"

typedef std::pair<std::string, float> label;

SCENARIO("aggregateResult for trivial test case") {
    NetInfo net = NetInfo("AlexNet", 3);
    PlatformInfo plat = PlatformInfo();

    std::vector<std::pair<PlatformInfo, float>> usage;
    usage.push_back(std::pair<PlatformInfo, float>(plat, 1));

    PerformanceData perfData = PerformanceData(1000, 20, usage);

    std::vector<int> dim = {256, 256, 3};
    ImageWrapper img = ImageWrapper(dim, "PathToFile");
    std::vector<label> labels = {label("car", 0.7), label("bike", 0.2), label("house", 0.05), label("bird", 0.025),
                                 label("cat", 0.025)};
    ImageResult imgRes = ImageResult(labels, img);
    std::vector<ImageResult> results = {imgRes};

    ClassificationResult clasRes = ClassificationResult(results, net, perfData);

    clasRes.aggregateResults();

    std::vector<std::pair<std::string, float>> aggLabels = clasRes.getAggregatedResults();
    auto labelIt = aggLabels.begin();

    REQUIRE(labelIt.operator*().first == "car");
    REQUIRE(labelIt.operator*().second == 0.7f);
    labelIt++;
    REQUIRE(labelIt.operator*().first == "bike");
    REQUIRE(labelIt.operator*().second == 0.2f);
    labelIt++;
    REQUIRE(labelIt.operator*().first == "house");
    REQUIRE(labelIt.operator*().second == 0.05f);
    labelIt++;
    REQUIRE(labelIt.operator*().first == "bird");
    REQUIRE(labelIt.operator*().second == 0.025f);
    labelIt++;
    REQUIRE(labelIt.operator*().first == "cat");
    REQUIRE(labelIt.operator*().second == 0.025f);
    
}