//
// Created by Maximilian Franz on 16.01.18.
//

#include <map>
#include <wrapper/DataWrapper.h>
#include <Interpreter.h>
#include <Executor.h>
#include <fstream>
#include <iostream>
#include <iterator>
#include <PreProcessor.h>

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

    ImageResult *r = t.getResult(&output, &i); // Add & as a quickfix to get pointers.

    auto mapresult = r->getResults().at(0);
    REQUIRE(mapresult.first == "label 3");
    REQUIRE(r->getImagePath() == "testpath");
    //Expected label 3, label 1, label 5, label 2,
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
        NetBuilder builder;
        std::vector<NetInfo*> nets = builder.queryAvailableNets();
        NetInfo alexnetinfo = *nets.at(0);
        NeuralNet* alexnet = builder.buildNeuralNet(alexnetinfo);

        std::vector<PlatformInfo*> platformsinfos_mock;

        p.placeComputations(alexnet, OperationMode::EnergyEfficient, platformsinfos_mock);
        REQUIRE(alexnet->isPlacementComplete());

    }

    SECTION("Testing Complete execution of the net") {
        Executor executor;
        std::vector<NetInfo*> nets = executor.queryNets();
        NetInfo alexnetinfo = *nets.at(0);

        std::string img_data_path = "../../../tests/resources/img_data.txt";

        std::vector<float> image = getDataFromFile(img_data_path);

        std::vector<int> imgDim = {3,227,227};
        ImageWrapper *img = new ImageWrapper(imgDim, image, "filepath");

        std::vector<ImageResult*> results;
        std::vector<PlatformInfo*> info_mock;
//        results = executor.classify({img}, alexnetinfo, OperationMode::EnergyEfficient, info_mock);
//
//        // Highest prob is weasel
//        REQUIRE(results.front()->getResults().front().first == "weasel");

    }

    SECTION("Testing PreProcessor and Execution") {
        PreProcessor p;
        p.setOutputSize(227,227);

        QImage img("../../../tests/resources/tf_data_script/laska.png");

        std::map<QString, QImage> map;
        map.insert(std::pair<QString, QImage>(QString("laska"), img));
        std::vector<ImageWrapper> images = p.processImages(map);

        std::vector<float> imData = images.front().getData();

        for (int i = 0; i < 10; i++) {
            std::cout << i << " : " << imData[i] << "\n";
        }

        Executor executor;
        std::vector<NetInfo*> nets = executor.queryNets();
        NetInfo alexnetinfo = *nets.at(0);




        std::vector<ImageResult*> results;
        std::vector<PlatformInfo*> info_mock;
        results = executor.classify({&images.front()}, alexnetinfo, OperationMode::EnergyEfficient, info_mock);

        std::cout << results.front()->getResults().front().first;

    }
}