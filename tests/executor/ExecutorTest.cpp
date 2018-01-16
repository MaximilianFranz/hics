//
// Created by Maximilian Franz on 16.01.18.
//

#include <map>
#include <wrapper/DataWrapper.h>
#include <Interpreter.h>
#include "ExecutorTest.h"

TEST_CASE("Testing Interpreter") {
    //Create example labelMap
    std::map<int, std::string> labelMap;
    labelMap.emplace(0, "label 0");
    labelMap.emplace(1, "label 1");
    labelMap.emplace(2, "label 2");
    labelMap.emplace(3, "label 3");
    labelMap.emplace(4, "label 4");
    labelMap.emplace(5, "label 5");

    // Create example outputWrapper
    std::vector<float> outputData = {1.0, 5.0, 3.0, 8.0, 2.0, 4.0};
    std::vector<int> dim(1,6);
    DataWrapper output(dim, outputData);

    // Init Interpreter
    Interpreter t(labelMap);
    // Create facade ImageWrapper
    ImageWrapper i(dim,outputData, "testpath");

    ImageResult r = t.getResult(output, i);

    auto mapresult = r.getResults().at(0);
    REQUIRE(mapresult.first == "label 3");
    REQUIRE(r.getImagePath() == "testpath");
    //Expected label 3, label 1, label 5, label 2,
}