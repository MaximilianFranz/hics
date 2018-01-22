//
// Created by Maximilian Franz on 22.01.18.
//

#include <map>
#include "NetBuilderTest.h"
#include "loader/LabelLoader.h"

TEST_CASE("Testing LabelLoader on alexnet labels") {
    std::string path = "../../../src/netbuilder/loader/alexnet_labels.txt";
    std::map<int, std::string> labelMap = LabelLoader::getLabelMap(path);

    REQUIRE(labelMap.at(1) == "goldfish, Carassius auratus");
}