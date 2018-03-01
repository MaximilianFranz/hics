/* Copyright 2018 The HICS Authors
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software withoutresults.front()->getResults().front().first
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
#include <Interpreter.h>
#include <Executor.h>
#include <fstream>
#include <iostream>
#include <iterator>
#include <PreProcessor.h>
#include <algorithm>

#include <QImage>

#include <wrapper/DataWrapper.h>
#include <FileHelper.h>


#include "ExecutorTest.h"

// HELPER METHODS for getting data from files

SCENARIO("Testing Executor Module") {

    SECTION("Testing Interpreter") {
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
        DataWrapper *output = new DataWrapper(dim, outputData);

        // Init Interpreter
        Interpreter t(labelMap);

        // Create facade ImageWrapper
        ImageWrapper i(dim, outputData, "testpath");

        PlatformPlacer *mock = new PlatformPlacer();

        // TODO: Mock computationDistribution or remove tests.
        ImageResult *r = t.getResult(output, &i, mock ); // Add & as a quickfix to get pointers.

        REQUIRE(r->getResults().at(0).first == "label 3");
        REQUIRE(r->getResults().at(1).first == "label 1");
        REQUIRE(r->getImagePath() == "testpath");
        //Expected label 3, label 1, label 5, label 2,
    }

    SECTION("Testing Placer") {
        PlatformPlacer p;
        Executor e;
        NetBuilder *builder = new NetBuilder();
        std::vector<NetInfo*> nets = builder->queryAvailableNets();
        NetInfo alexnetinfo = *nets.at(0); // AlexNet
        NeuralNet* alexnet = builder->buildNeuralNet(alexnetinfo);

        std::vector<PlatformInfo*> platforminfos = e.queryPlatform();

        p.placeComputations(alexnet, OperationMode::EnergyEfficient, platforminfos);
        REQUIRE(alexnet->isPlacementComplete());
        REQUIRE(alexnet->getLastLayer()->getType() == LayerType::LOSS_SOFTMAX);

    }

    SECTION("Testing Complete execution of the net with TF input") {
        Executor *executor = new Executor;
        std::vector<NetInfo*> nets = executor->queryNets();
        NetInfo alexnetinfo = *nets.at(0);

        // Use preprocessed data exported from tensorflow python implementation
        std::string img_data_path = TEST_RES_DIR "img_data.txt";

        std::vector<float> image = util::getDataFromFile(img_data_path);

        std::vector<int> imgDim = {3,227,227};
        ImageWrapper *img = new ImageWrapper(imgDim, image, "filepath");


        std::vector<PlatformInfo*> info = executor->queryPlatform();
        std::vector<ImageResult*> results = executor->classify({img},
                                                               alexnetinfo,
                                                               OperationMode::EnergyEfficient,
                                                               info);

        // Highest prob is weasel
        REQUIRE(results.front()->getResults().front().first == "weasel");

        delete executor;

    }

    SECTION("Testing PreProcessor and Execution with real image") {
        //
        PreProcessor p;
        p.setOutputSize(227,227);

        QImage img(TEST_RES_DIR "tf_data_script/laska.png");
        std::map<QString, QImage> map;
        map.insert(std::pair<QString, QImage>(QString("laska"), img));
        std::vector<ImageWrapper*> images = p.processImages(map);

        Executor executor;
        std::vector<NetInfo*> nets = executor.queryNets();
        NetInfo alexnetinfo = *nets.at(0);
        std::vector<PlatformInfo*> infos = executor.queryPlatform();

        PlatformInfo* cpu = nullptr;
        PlatformInfo* fpga = nullptr;

        // Specify CPU and FPGA Platform out of the available platforms
        for (auto p : infos) {
            if (p->getType() == PlatformType::CPU )
                cpu = p;
            if (p->getType() == PlatformType::FPGA)
                fpga = p;
        }

        REQUIRE(fpga != nullptr );
        REQUIRE(cpu != nullptr );

        SECTION("EnergyEfficient Mode with all platforms") {
            // Use all platforms
            std::vector<ImageResult*> results = executor.classify({images.front()},
                                                                  alexnetinfo,
                                                                  OperationMode::EnergyEfficient,
                                                                  infos);

            REQUIRE(results.front()->getResults().front().first == "weasel");

            if (results.front()->getCompDistribution().front().first->getType() == PlatformType::CPU){
                REQUIRE(results.front()->getCompDistribution().front().second > 0.5);
            }
        }

        SECTION("HighPower Mode with all platforms") {
            // Use all platforms
            std::vector<ImageResult*> results = executor.classify({images.front()},
                                                                  alexnetinfo,
                                                                  OperationMode::HighPower,
                                                                  infos);

            REQUIRE(results.front()->getResults().front().first == "weasel");

            if (results.front()->getCompDistribution().front().first->getType() == PlatformType::CPU){
                REQUIRE(results.front()->getCompDistribution().front().second > 0.5);
            }
        }

        SECTION("LowPower Mode with all platforms") {
            // Use all platforms
            std::vector<ImageResult*> results = executor.classify({images.front()},
                                                                  alexnetinfo,
                                                                  OperationMode::LowPower,
                                                                  infos);

            REQUIRE(results.front()->getResults().front().first == "weasel");

            if (results.front()->getCompDistribution().front().first->getType() == PlatformType::CPU){
                REQUIRE(results.front()->getCompDistribution().front().second > 0.9);
            }
        }

        SECTION("Test exception when no platform is inserted") {
            // Use all platforms
            infos.clear();
            REQUIRE_THROWS(executor.classify({images.front()},
                                             alexnetinfo,
                                             OperationMode::LowPower,
                                             infos));
        }


    }
}
