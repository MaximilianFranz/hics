//
// Created by Maximilian Franz on 22.01.18.
//

#include <map>
#include <loader/ModelLoader.h>
#include <loader/ModelCrawler.h>
#include "NetBuilder.h"
#include <iostream>
#include "NetBuilderTest.h"
#include "loader/LabelLoader.h"

//Describe path without closing "/"!!!
const std::string MODEL_DIR = "../../../src/netbuilder/loader/models";

TEST_CASE("Testing LabelLoader on alexnet labels") {
    //TODO: Change if models folder is moved to resources/
    std::string path = "../../../src/netbuilder/loader/models/alexnet_labels.txt";
    std::map<int, std::string> labelMap = LabelLoader::getLabelMap(path);

    REQUIRE(labelMap.at(1) == "goldfish, Carassius auratus");
}


TEST_CASE("Testing ModelCrawler file listing") {
    std::vector<std::string> filenames = ModelCrawler::getFilesInDir(MODEL_DIR);
    REQUIRE(MODEL_DIR + "/alexnet_labels.txt" == filenames[0]);
    REQUIRE(MODEL_DIR + "/alexnet.json" == filenames[1]);
}

TEST_CASE("Testing ModelCrawler NetInfo creation") {
    std::vector<NetInfo*> availableNets = ModelCrawler::getValidNets(MODEL_DIR);
    REQUIRE(availableNets.size() != 0);
    REQUIRE(availableNets[0]->getIdentifier() == "alexnet");
}

SCENARIO("Testing Netbuilder methods") {
    NetBuilder n;
    SECTION("Loading Labels from NetInfo") {
        std::vector<NetInfo*> availableNets = ModelCrawler::getValidNets(MODEL_DIR);
        std::map<int, std::string> labelMap = n.getLabelMap(availableNets[0]);
        REQUIRE(labelMap.at(1) == "goldfish, Carassius auratus");
    }

    SECTION("Building Net") {
        //Get first and only model
        NetInfo *netInfo = ModelCrawler::getValidNets(MODEL_DIR)[0];
        NeuralNet* net =  n.buildNeuralNet(*netInfo);
        REQUIRE(net->getLastLayer()->getType() == LayerType::LOSS_SOFTMAX);
    }
}