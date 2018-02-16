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

#include <map>
#include <iostream>
#include <algorithm>

#include "loader/ModelLoader.h"
#include "loader/ModelCrawler.h"
#include "loader/LabelLoader.h"

#include "NetBuilder.h"
#include "NetBuilderTest.h"

//Describe path without closing "/"!!!
const std::string MODEL_DIR = RES_DIR "models";

TEST_CASE("Testing LabelLoader on alexnet labels") {
    //TODO: Change if models folder is moved to resources/
    std::string path = RES_DIR "models/alexnet_labels.txt";
    std::map<int, std::string> labelMap = LabelLoader::getLabelMap(path);

    REQUIRE(labelMap.at(1) == "goldfish, Carassius auratus");
}


TEST_CASE("Testing ModelCrawler file listing") {
    std::vector<std::string> filenames = ModelCrawler::getFilesInDir(MODEL_DIR);
    REQUIRE(std::find(filenames.begin(), filenames.end(), MODEL_DIR + "/alexnet_labels.txt") != filenames.end());
    REQUIRE(std::find(filenames.begin(), filenames.end(), MODEL_DIR + "/alexnet.json") != filenames.end());
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