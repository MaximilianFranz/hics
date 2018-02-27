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
#include <wrapper/DataWrapper.h>
#include <Interpreter.h>
#include <Executor.h>
#include <fstream>
#include <iostream>
#include <iterator>
#include <PreProcessor.h>
#include <algorithm>

#include <QImage>


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

    //TODO: Mock computationDistribution or remove tests.
//    ImageResult *r = t.getResult(&output, &i, nullptr); // Add & as a quickfix to get pointers.
//
//    auto mapresult = r->getResults().at(0);
//    REQUIRE(mapresult.first == "label 3");
//    REQUIRE(r->getImagePath() == "testpath");
//    //Expected label 3, label 1, label 5, label 2,
}


template<typename T>
std::vector<T> split(const std::string& line) {
    std::istringstream is(line);
    return std::vector<T>(std::istream_iterator<T>(is), std::istream_iterator<T>());
}

std::vector<float> getDataFromFile(std::string path) {
    char* resolved_path;
    // Getting the real path from execution dir.
    // We pass NULL and let realpath allocate the string which means we have to free() it later.
    resolved_path = realpath(path.c_str(), NULL);
    // Open file
    std::ifstream file(resolved_path);
    std::string str;

    file.seekg(0, std::ios::end);
    str.reserve(static_cast<unsigned long>(file.tellg()));
    file.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(file)),
               std::istreambuf_iterator<char>());

    std::vector<float> data = split<float>(str);

    free(resolved_path);
    return data;
}

SCENARIO("Testing Executor Module") {


    SECTION("Testing Placer") {
        PlatformPlacer p;
        Executor e;
        NetBuilder *builder = new NetBuilder();
        std::vector<NetInfo*> nets = builder->queryAvailableNets();
        NetInfo alexnetinfo = *nets.at(0);
        NeuralNet* alexnet = builder->buildNeuralNet(alexnetinfo);

        std::vector<PlatformInfo*> platforminfos = e.queryPlatform();

        p.placeComputations(alexnet, OperationMode::EnergyEfficient, platforminfos);
        REQUIRE(alexnet->isPlacementComplete());

    }

    SECTION("Testing Complete execution of the net") {
        Executor *executor = new Executor;
        std::vector<NetInfo*> nets = executor->queryNets();
        NetInfo alexnetinfo = *nets.at(0);

        std::string img_data_path = TEST_RES_DIR "img_data.txt";

        std::vector<float> image = getDataFromFile(img_data_path);

        std::vector<int> imgDim = {3,227,227};
        ImageWrapper *img = new ImageWrapper(imgDim, image, "filepath");

        std::vector<ImageResult*> results;
        std::vector<PlatformInfo*> info = executor->queryPlatform();
        results = executor->classify({img}, alexnetinfo, OperationMode::EnergyEfficient, info);

        // Highest prob is weasel
        REQUIRE(results.front()->getResults().front().first == "weasel");

        delete executor;

    }

    SECTION("Testing PreProcessor and Execution") {
        PreProcessor p;
        p.setOutputSize(227,227);

        QImage img(TEST_RES_DIR "tf_data_script/laska.png");

        std::map<QString, QImage> map;
        map.insert(std::pair<QString, QImage>(QString("laska"), img));
        std::vector<ImageWrapper*> images = p.processImages(map);

        Executor executor;
        std::vector<NetInfo*> nets = executor.queryNets();
        NetInfo alexnetinfo = *nets.at(0);

        std::vector<ImageResult*> results;
        std::vector<PlatformInfo*> infos = executor.queryPlatform();
        results = executor.classify({images.front()}, alexnetinfo, OperationMode::EnergyEfficient, infos);

        std::cout << results.front()->getResults().front().first << std::endl;
        std::cout << results.front()->getResults().front().second << std::endl;

    }
}