//
// Created by michael on 15.01.18.
//

#include <wrapper/DataWrapper.h>

#include <PlatformManager.h>
#include <iostream>
#include "PlatformTest.h"

TEST_CASE("Activation ReLU test") {
    PlatformManager& pm = PlatformManager::getInstance();
    REQUIRE(pm.getPlatforms().size() >= 1);

    Platform* p = pm.getPlatforms().at(0);
    REQUIRE(p != nullptr);

    ActivationFunction* f = p->createActivationFunction(LayerType::ACTIVATION_RELU);
    REQUIRE(f != nullptr);

    std::vector<float> data = {0, 2.2, -3.3f, 4.4, -5.5f};
    std::vector<int> s(1, 5);
    DataWrapper in(s, data);
    DataWrapper out(s);

    f->execute(in, out);
    REQUIRE(out.getData().at(0) == 0);
    REQUIRE(out.getData().at(1) == 2.2f);
    REQUIRE(out.getData().at(2) == 0);
    REQUIRE(out.getData().at(3) == 4.4f);
    REQUIRE(out.getData().at(4) == 0);

}
TEST_CASE("Convolution test") {
    int inSize = 11;
    int stride = 1;
    int padding = 0;
    int filterSize = 3;
    int outSize = (inSize - filterSize + 2 * padding) / stride + 1;
    int numFilters = 1;
    int numPlanes = 2;

    /* input data */
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

    /* output data */
    DataWrapper output({numFilters, outSize, outSize});

    /* filter data and bias data */
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

    PlatformManager& pm = PlatformManager::getInstance();
    REQUIRE(pm.getPlatforms().size() >= 1);

    Platform* p = pm.getPlatforms().at(0);
    REQUIRE(p != nullptr);

    ConvolutionFunction* f = p->createConvolutionFunction();
    REQUIRE(f != nullptr);

    f->execute(input, output, weights, stride, filterSize, numFilters, padding);

    REQUIRE(output.getData().at(0) == 234.5f);
}
