//
// Created by jallmenroeder on 19/01/18.
//

#include "ClassificationResultTest.h"

typedef std::pair<std::string, float> label;

const float eps = std::numeric_limits<float>::epsilon();

SCENARIO("aggregateResult for trivial test case") {
    NetInfo net = NetInfo("AlexNet", 3);
    PlatformInfo plat = PlatformInfo();

    std::vector<std::pair<PlatformInfo, float>> usage;
    usage.emplace_back(std::pair<PlatformInfo, float>(plat, 1));

    PerformanceData perfData = PerformanceData(1000, 20, usage);

    std::vector<int> dim1 = {256, 256, 3};
    ImageWrapper img1 = ImageWrapper(dim1, "PathToFile");
    std::vector<label> labels1 = {label("car", 0.7), label("bike", 0.2), label("house", 0.05), label("bird", 0.025),
                                 label("cat", 0.025)};
    ImageResult imgRes1 = ImageResult(labels1, img1);

    std::vector<int> dim2 = {256, 256, 3};
    ImageWrapper img2 = ImageWrapper(dim2, "PathToFile");
    std::vector<label> labels2 = {label("car", 0.8), label("bike", 0.1), label("house", 0.09), label("dog", 0.005),
                                  label("cat", 0.005)};
    ImageResult imgRes2 = ImageResult(labels2, img2);



    SECTION("test case with only one result") {
        std::vector<ImageResult> results = {imgRes1};

        ClassificationResult clasRes = ClassificationResult(results, net, perfData);

        clasRes.aggregateResults();

        std::vector<std::pair<std::string, float>> aggLabels = clasRes.getAggregatedResults();
        auto labelIt = aggLabels.begin();

        REQUIRE(labelIt.operator*().first == "car");
        REQUIRE(std::abs(labelIt.operator*().second - 0.7f) < eps);
        labelIt++;
        REQUIRE(labelIt.operator*().first == "bike");
        REQUIRE(std::abs(labelIt.operator*().second - 0.2f) < eps);
        labelIt++;
        REQUIRE(labelIt.operator*().first == "house");
        REQUIRE(std::abs(labelIt.operator*().second - 0.05f) < eps);
        labelIt++;
        REQUIRE(labelIt.operator*().first == "bird");
        REQUIRE(std::abs(labelIt.operator*().second - 0.025f) < eps);
        labelIt++;
        REQUIRE(labelIt.operator*().first == "cat");
        REQUIRE(std::abs(labelIt.operator*().second - 0.025f) < eps);
    }

    SECTION("Aggregate two results") {
        std::vector<ImageResult> results = {imgRes1, imgRes2};

        ClassificationResult clasRes = ClassificationResult(results, net, perfData);
        clasRes.aggregateResults();

        std::vector<std::pair<std::string, float>> aggLabels = clasRes.getAggregatedResults();

        REQUIRE(aggLabels.size() == 5);
        auto labelIt = aggLabels.begin();

        REQUIRE(labelIt.operator*().first == "car");
        REQUIRE(std::abs(labelIt.operator*().second - 0.75f) < eps);
        labelIt++;
        REQUIRE(labelIt.operator*().first == "bike");
        REQUIRE(std::abs(labelIt.operator*().second - 0.15f) < eps);
        labelIt++;
        REQUIRE(labelIt.operator*().first == "house");
        REQUIRE(std::abs(labelIt.operator*().second - 0.07f) < eps);
        labelIt++;
        REQUIRE(labelIt.operator*().first == "cat");
        REQUIRE(std::abs(labelIt.operator*().second - 0.015f) < eps);
        labelIt++;
        REQUIRE(labelIt.operator*().first == "bird");
        REQUIRE(std::abs(labelIt.operator*().second - 0.0125f) < eps);
    }
    
}