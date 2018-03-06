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

#include <LayerMaker.h>
#include <loader/JSONModelLoader.h>
#include <NetBuilder.h>
#include <NetInfo.h>
#include <iostream>
#include <layers/naive/ConcatLayer.h>
#include "NeuralNetTest.h"

SCENARIO("Testing Layer") {
    LayerMaker l;
    std::string path = RES_DIR "models/alexnet.json";
    JSONModelLoader m(path);
    std::vector<int> v{3, 227, 227};

    LayerConstructionParams lcp = m.getLayerConstructionParamsByIndex(1);
    ConvolutionLayer* conv = l.createConvLayer(lcp, v, NULL);

    REQUIRE(conv->getNextLayer() == nullptr);
    REQUIRE(conv->getPreviousLayer() == nullptr);

    SECTION("Layer in full net") {
        auto *builder = new NetBuilder();
        std::vector<NetInfo*> nets = builder->queryAvailableNets();
        NetInfo alexnetinfo = *nets.at(0); // AlexNet
        NeuralNet* alexnet = builder->buildNeuralNet(alexnetinfo);

        auto lastLayer = alexnet->getLastLayer();
        auto secondLastLayer = lastLayer->getPreviousLayer();

        REQUIRE(lastLayer->getPreviousLayer()->getType() == LayerType::FULLYCONNECTED);
        REQUIRE(secondLastLayer->getNextLayer()->getType() == LayerType::LOSS_SOFTMAX);
    }


}

TEST_CASE("Testing LayerType output") {
    std::vector<std::string> names = {"ACTIVATION_RELU",
                                      "NORMALIZATION_LOCALRESPONSE",
                                      "LOSS_SOFTMAX",
                                      "POOLING_MAX",
                                      "CONVOLUTION",
                                      "FULLYCONNECTED",
                                      "INPUT",
                                      "CONCAT",
    };

    for (int i = 0; i < 8; i++) {
        std::stringstream buffer;
        buffer << (LayerType)i;
        REQUIRE(buffer.str() == names[i]);
    }
}

TEST_CASE("Convolution with numGroup > 2 throws Exception") {
    LayerMaker l;
    std::string path = RES_DIR "models/alexnet.json";
    JSONModelLoader m(path);
    std::vector<int> v{3, 227, 227};

    LayerConstructionParams lcp = m.getLayerConstructionParamsByIndex(1);
    lcp.numGroups = 3;
    ConvolutionLayer* conv = l.createConvLayer(lcp, v, NULL);

    // numgroups = 3 is not implemented and thus an Exception is thrown
    REQUIRE_THROWS(conv->forward());
}

TEST_CASE("Testing ConcatLayer seperately") {
    // The ConcatLayer needs further consideration and implementation if
    // other net should be used.

    LayerMaker l;
    std::string path = RES_DIR "models/alexnet.json";
    JSONModelLoader m(path);
    std::vector<int> v{3, 227, 227};

    LayerConstructionParams lcp = m.getLayerConstructionParamsByIndex(1);
    lcp.numGroups = 3;
    ConvolutionLayer* conv = l.createConvLayer(lcp, v, NULL);

    std::vector<int> v1{3, 227, 227};
    std::vector<int> v2{3, 227, 227};
    std::vector<int> v3{3, 227, 227};

    std::vector<std::vector<int>> dims = {v1, v2, v3};

    auto c = new ConcatLayer(dims);

    c->setPreviousLayer(conv);


    // Not Implemented Yet
    REQUIRE_THROWS(c->forward());

    REQUIRE(c->getOutputDimensions().at(0) == 9);
    REQUIRE(c->getPreviousLayer()->getType() == LayerType::CONVOLUTION);

}


// For tests of getter, setter and constructors see NetBuilderTests