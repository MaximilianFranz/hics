//
// Created by Maximilian Franz on 17.01.18.
//

#include <LayerMaker.h>
#include <iostream>
#include <loader/JSONModelLoader.h>
#include "LayerMakerTest.h"


SCENARIO("Testing construction of Layers" , "[layermaker]") {

    SECTION("InputLayer") {
        LayerMaker l;
        std::string path ="../src/netbuilder/loader/alexnet.json";
        JSONModelLoader m(path);
        LayerConstructionParams lcp = m.getLayerConstructionParamsByIndex(0);
        REQUIRE(lcp.type == "input");
        InputLayer* input = l.createInputLayer(lcp);
        LocalResponseNormLayer* lrn = l.createLocalResponseNormLayer(lcp);
//        std::vector<int> v{3, 227, 227};
//        REQUIRE(input->getInputDimensions() == v);
    }

//    SECTION("ConvolutionLayer") {
//        LayerMaker l;
//        std::string path;
//    }
}