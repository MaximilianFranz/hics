//
// Created by Maximilian Franz on 22.01.18.
//

#include <map>
#include "NetBuilderTest.h"
#include "loader/LabelLoader.h"

TEST_CASE("Testing LabelLoader on alexnet labels") {
    //TODO: Change if models folder is moved to resources/
    std::string path = "../../../src/netbuilder/loader/models/alexnet_labels.txt";
    std::map<int, std::string> labelMap = LabelLoader::getLabelMap(path);

    REQUIRE(labelMap.at(1) == "goldfish, Carassius auratus");
}