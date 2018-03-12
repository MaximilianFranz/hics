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

#include <loader/weightloader/AlexNetWeightLoader.h>
#include <ResourceException.h>
#include "AlexNetWeightLoaderTest.h"

TEST_CASE("AlexNetWeightLoader can read the weight file and access its contents", "[alexnetweightloadertest]") {


    SECTION ("Initialize and return all layer", "[alexnetweightloadertest_initialize]") {
        AlexNetWeightLoader loader(RES_DIR "weights/alexnet_weights.h5");
        std::vector<int> dimensions{96, 3, 11, 11};
        WeightWrapper *wrapper = loader.getWeights(WeightLoader::LayerIdentifier::CONV_1);
        REQUIRE(wrapper->getDimensions()[0] == 96);
        REQUIRE(wrapper->getDimensions()[1] == 3);
        REQUIRE(wrapper->getDimensions()[2] == 11);
        REQUIRE(wrapper->getDimensions()[3] == 11);
        delete wrapper;

        wrapper = loader.getWeights(WeightLoader::LayerIdentifier::CONV_2);
        REQUIRE(wrapper->getDimensions()[0] == 256);
        REQUIRE(wrapper->getDimensions()[1] == 48);
        REQUIRE(wrapper->getDimensions()[2] == 5);
        REQUIRE(wrapper->getDimensions()[3] == 5);
        delete wrapper;

        wrapper = loader.getWeights(WeightLoader::LayerIdentifier::CONV_3);
        REQUIRE(wrapper->getDimensions()[0] == 384);
        REQUIRE(wrapper->getDimensions()[1] == 256);
        REQUIRE(wrapper->getDimensions()[2] == 3);
        REQUIRE(wrapper->getDimensions()[3] == 3);
        delete wrapper;

        wrapper = loader.getWeights(WeightLoader::LayerIdentifier::CONV_4);
        REQUIRE(wrapper->getDimensions()[0] == 384);
        REQUIRE(wrapper->getDimensions()[1] == 192);
        REQUIRE(wrapper->getDimensions()[2] == 3);
        REQUIRE(wrapper->getDimensions()[3] == 3);
        delete wrapper;

        wrapper = loader.getWeights(WeightLoader::LayerIdentifier::CONV_5);
        REQUIRE(wrapper->getDimensions()[0] == 256);
        REQUIRE(wrapper->getDimensions()[1] == 192);
        REQUIRE(wrapper->getDimensions()[2] == 3);
        REQUIRE(wrapper->getDimensions()[3] == 3);
        delete wrapper;

        wrapper = loader.getWeights(WeightLoader::LayerIdentifier::FULLY_CON_1);
        REQUIRE(wrapper->getDimensions()[0] == 4096);
        REQUIRE(wrapper->getDimensions()[1] == 9216);
        delete wrapper;

        wrapper = loader.getWeights(WeightLoader::LayerIdentifier::FULLY_CON_2);
        REQUIRE(wrapper->getDimensions()[0] == 4096);
        REQUIRE(wrapper->getDimensions()[1] == 4096);
        delete wrapper;

        wrapper = loader.getWeights(WeightLoader::LayerIdentifier::FULLY_CON_3);
        REQUIRE(wrapper->getDimensions()[0] == 1000);
        REQUIRE(wrapper->getDimensions()[1] == 4096);
        delete wrapper;
    }

    SECTION("Wrong file path", "[alexnetweightloadertest_wrongpath]") {
        bool exceptionCatched = false;
        try {
            AlexNetWeightLoader loader("wrongpath.h5");
        } catch (ResourceException &e) {
            //Succes if a Ressource Exception has been thrown
            exceptionCatched = true;
        }

        REQUIRE(exceptionCatched);
    }

    SECTION("Wrong group name for the weights", "[alexnetweightloadertest_wronggroupname") {
        bool exceptionCatched = false;
        try {
            AlexNetWeightLoader loader(TEST_RES_DIR "/testing_false_weights/false_group_name.h5");
            WeightWrapper *wrapper = loader.getWeights(WeightLoader::LayerIdentifier::CONV_1);
        } catch (ResourceException &e) {
            exceptionCatched = true;
        }

        REQUIRE(exceptionCatched);
    }

    SECTION("Right group name but empty dataspace", "[alexnetweightloadertest_emptydataspace") {
        bool exceptionCatched = false;
        try {
            AlexNetWeightLoader loader(TEST_RES_DIR "/testing_false_weights/right_group_name_empty_dataspace.h5");
            WeightWrapper *wrapper = loader.getWeights(WeightLoader::LayerIdentifier::CONV_1);
        } catch (ResourceException &e) {
            exceptionCatched = true;
        }

        REQUIRE(exceptionCatched);
    }

    SECTION("Right group name, non empty dataspace but wrong bias name ", "[alexnetweightloadertest_wrongbiasname") {
        bool exceptionCatched = false;
        try {
            AlexNetWeightLoader loader(TEST_RES_DIR "/testing_false_weights/false_bias_name.h5");
            WeightWrapper *wrapper = loader.getWeights(WeightLoader::LayerIdentifier::CONV_1);
        } catch (ResourceException &e) {
            exceptionCatched = true;
        }

        REQUIRE(exceptionCatched);
    }

    SECTION("Right group name, non empty dataspace, right bias name but empty bias dataspace",
            "[alexnetweightloadertest_emptybiasdataspace") {
        bool exceptionCatched = false;
        try {
            AlexNetWeightLoader loader(TEST_RES_DIR "/testing_false_weights/right_group_name_empty_bias_dataspace.h5");
            WeightWrapper *wrapper = loader.getWeights(WeightLoader::LayerIdentifier::CONV_1);
        } catch (ResourceException &e) {
            exceptionCatched = true;
        }

        REQUIRE(exceptionCatched);
    }
}
