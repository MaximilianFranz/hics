//
// Created by michael on 15.01.18.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>

#include <wrapper/DataWrapper.h>

#include <PlatformManager.h>

#include "PlatformTest.h"

TEST_CASE("Activation ReLU test") {
    PlatformManager& pm = PlatformManager::getInstance();
    REQUIRE(pm.getPlatforms().size() >= 1);

    Platform *p = pm.getPlatforms()[0];
    REQUIRE(p != nullptr);

    ActivationFunction *f = p->createActivationFunction(LayerType::ACTIVATION_RELU);
    REQUIRE(f != nullptr);

    std::vector<float> data = {0, 2.2, -3.3f, 4.4, -5.5f};
    std::vector<int> s(1, 5);
    DataWrapper in(s, data);
    DataWrapper out(s);

    f->execute(in, out);
    REQUIRE(out.getData()[0] == 0);
    REQUIRE(out.getData()[1] == 2.2f);
    REQUIRE(out.getData()[2] == 0);
    REQUIRE(out.getData()[3] == 4.4f);
    REQUIRE(out.getData()[4] == 0);

}

TEST_CASE("Convolution test") {
    int inSize = 11;
    int stride = 1;
    int padding = 0;
    int filterSize = 3;
    int outSize = (inSize - filterSize + 2 * padding) / stride + 1;
    int numFilters = 1;
    int numPlanes = 2;

    // generate input data
    std::vector<float> data;
    for (int y = 0 ; y < inSize; y++) {
        for (int x = 0; x < inSize; x++) {
            data.push_back(x+y);
        }
    }
    for (int y = 0 ; y < inSize; y++) {
        for (int x = 0; x < inSize; x++) {
            data.push_back(2*(x+y));
        }
    }

    DataWrapper input({numPlanes, inSize, inSize}, data);

    // output data
    DataWrapper output({numFilters, outSize, outSize});

    // filter data and bias data
    std::vector<float> filterData = {
            1,1,1,
            2,2,2,
            3,3,3,

            4,4,4,
            5,5,5,
            6,6,6,

    };
    std::vector<int> filterDim = {numPlanes, filterSize, filterSize};

    std::vector<float> biasData = {
            0.5
    };
    std::vector<int> biasDim = {numFilters};

    WeightWrapper weights(filterDim, filterData, biasData, biasDim);

    PlatformManager &pm = PlatformManager::getInstance();
    REQUIRE(pm.getPlatforms().size() >= 1);

    Platform *p = pm.getPlatforms()[0];
    REQUIRE(p != nullptr);

    ConvolutionFunction *f = p->createConvolutionFunction();
    REQUIRE(f != nullptr);

    f->execute(input, output, weights, stride, filterSize, numFilters, padding);

    REQUIRE(output.getData()[0] == 234.5f);
    REQUIRE(output.getData()[10] == 450.5f);
    REQUIRE(output.getSizeOfDimension(2) == 9);


    // This time with padding
    padding = 1;
    outSize = (inSize - filterSize + 2 * padding) / stride + 1;
    output = DataWrapper({numFilters, outSize, outSize});

    f->execute(input, output, weights, stride, filterSize, numFilters, padding);

    REQUIRE(output.getData()[0] == 57.5f);
    REQUIRE(output.getData()[12] == 234.5f);
    REQUIRE(output.getData()[24] == 450.5f);
    REQUIRE(output.getSizeOfDimension(2) == 11);

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

TEST_CASE("Realdata Convolution Test") {
    std::string img_data_path = "../../../tests/resources/img_data.txt";
    std::string conv1_bias_path = "../../../tests/resources/conv1_bias.txt";
    std::string conv1_weights_path = "../../../tests/resources/conv1_weight.txt";
    std::string conv1_result_path = "../../../tests/resources/conv1_data_alexnet.txt";

    std::vector<float> weights = getDataFromFile(conv1_weights_path);
    std::vector<float> bias = getDataFromFile(conv1_bias_path);
    std::vector<float> result = getDataFromFile(conv1_result_path);
    std::vector<float> image = getDataFromFile(img_data_path);

    std::vector<int> weightDim = {96,3,11,11};
    std::vector<int> biasDim = {96};
    WeightWrapper weightsWrapper(weightDim, weights, bias, biasDim);

    std::vector<int> inDim = {3, 227, 227};
    std::vector<int> outDim = {96, 55, 55};

    DataWrapper in(inDim, image);
    DataWrapper out_real(outDim);
    DataWrapper out_expected(outDim, result);

    PlatformManager &pm = PlatformManager::getInstance();
    REQUIRE(pm.getPlatforms().size() >= 1);

    Platform *p = pm.getPlatforms()[0];
    REQUIRE(p != nullptr);

    ConvolutionFunction *f = p->createConvolutionFunction();
    REQUIRE(f != nullptr);

    f->execute(in, out_real, weightsWrapper, 4, 11, 96, 0);
    // out_real evaluates to 0 from i = 4 onwards

    for (int i = 0; i < 55*55; i++) { // Test the first filter fully
        REQUIRE(abs(out_real.getData()[i] - out_expected.getData()[i]) < 0.01);
    }

    for (int i = 0; i < 55*55*96; i += 2000) { // Pick one or two samples for each filter
        REQUIRE(abs(out_real.getData()[i] - out_expected.getData()[i]) < 0.01);
    }

}
