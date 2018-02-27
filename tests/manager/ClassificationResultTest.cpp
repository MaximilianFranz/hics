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

#include "ClassificationResultTest.h"

typedef std::pair<std::string, float> label;

const float eps = std::numeric_limits<float>::epsilon();

SCENARIO("aggregateResult for trivial test case") {
    NetInfo net = NetInfo("AlexNet", 3, "alexnet");
    PlatformInfo plat = PlatformInfo();

    std::vector<std::pair<PlatformInfo*, float>> usage;
    usage.emplace_back(std::pair<PlatformInfo*, float>(&plat, 1));

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