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

#include "UtilTest.h"
#include "Util.h"
#include "Communicator.grpc.pb.h"
#include "Communicator.pb.h"

SCENARIO("Test") {
    PlatformInfo cpu = PlatformInfo("internal CPU", PlatformType::CPU, "0", 500, 20000);
    PlatformInfo gpu = PlatformInfo("internal GPU", PlatformType::GPU, "1", 1000, 40000);
    PlatformInfo fpga = PlatformInfo("remote FPGA", PlatformType::FPGA, "2", 50, 200);
    PlatformInfo cl_cpu = PlatformInfo("CL CPU", PlatformType::CL_CPU, "3", 100, 400);

    std::vector<PlatformInfo*> platforms = {&cpu, &gpu, &fpga};

    NetInfo alexNet = NetInfo("Alex Net", 3, "alexNet");
    NetInfo googleNet = NetInfo("GoogLeNet", 3, "googleNet");

    std::vector<int> dim = {10, 10, 3};
    std::vector<float> data;
    for (int i = 0; i < 10*10*3; i++) {
        data.emplace_back(i);
    }

    ImageWrapper img = ImageWrapper(dim, data, "src/img");

    std::vector<NetInfo*> nets = {&alexNet, &googleNet};

    std::vector<std::pair<std::string, float>> labels;
    labels.emplace_back("dog", .8f);
    labels.emplace_back("cat", .1f);
    labels.emplace_back("bird", .05f);
    labels.emplace_back("house", .025f);
    labels.emplace_back("garage", .0125f);

    std::vector<std::pair<PlatformInfo*, float>> dist;
    dist.emplace_back(&cpu, .6);
    dist.emplace_back(&gpu, .4);
    std::vector<std::pair<PlatformInfo*, float>> dist2;
    dist2.emplace_back(&gpu, .6);
    dist2.emplace_back(&cpu, .4);
    std::vector<std::pair<PlatformInfo*, float>> dist3;
    dist3.emplace_back(&cpu, 1);
    dist3.emplace_back(&gpu, 0);
    ImageResult imgRes = ImageResult(labels, dist, img);
    ImageResult imgRes2 = ImageResult(labels, dist2, img);
    ImageResult imgRes3 = ImageResult(labels, dist3, img);

    SECTION("PlatformInfo to message") {
        auto *platMes = new PlatformInfoMessage();

        Util::platformInfoToMessage(&cpu, platMes);

        REQUIRE(platMes->description() == "internal CPU");
        REQUIRE(platMes->type() == PlatformInfoMessage::CPU);
        REQUIRE(platMes->platformid() == "0");
        REQUIRE(platMes->powerconsumption() == 500);
        REQUIRE(platMes->flops() == 20000);

        platMes = new PlatformInfoMessage();

        Util::platformInfoToMessage(&gpu, platMes);

        REQUIRE(platMes->description() == "internal GPU");
        REQUIRE(platMes->type() == PlatformInfoMessage::GPU);
        REQUIRE(platMes->platformid() == "1");
        REQUIRE(platMes->powerconsumption() == 1000);
        REQUIRE(platMes->flops() == 40000);

        platMes = new PlatformInfoMessage();

        Util::platformInfoToMessage(&fpga, platMes);

        REQUIRE(platMes->description() == "remote FPGA");
        REQUIRE(platMes->type() == PlatformInfoMessage::FPGA);
        REQUIRE(platMes->platformid() == "2");
        REQUIRE(platMes->powerconsumption() == 50);
        REQUIRE(platMes->flops() == 200);

        platMes = new PlatformInfoMessage();

        Util::platformInfoToMessage(&cl_cpu, platMes);

        REQUIRE(platMes->description() == "CL CPU");
        REQUIRE(platMes->type() == PlatformInfoMessage::CL_CPU);
        REQUIRE(platMes->platformid() == "3");
        REQUIRE(platMes->powerconsumption() == 100);
        REQUIRE(platMes->flops() == 400);

    }

    SECTION("NetInfo to Message") {
        NetInfoMessage *netMes = new NetInfoMessage();
        Util::netInfoToMessage(&alexNet, netMes);

        REQUIRE(netMes->name() == "Alex Net");
        REQUIRE(netMes->imagedimension() == 3);
        REQUIRE(netMes->identifier() == "alexNet");

        netMes = new NetInfoMessage();
        Util::netInfoToMessage(&googleNet, netMes);

        REQUIRE(netMes->name() == "GoogLeNet");
        REQUIRE(netMes->imagedimension() == 3);
        REQUIRE(netMes->identifier() == "googleNet");
    }

    SECTION("ImageWrapper to Message") {
        ImageWrapperMessage* imgMes = new ImageWrapperMessage();
        Util::imageWrapperToMessage(&img, imgMes);

        REQUIRE(imgMes->filepath() == "src/img");
        REQUIRE(imgMes->dimensions(0) == 10);
        REQUIRE(imgMes->dimensions(1) == 10);
        REQUIRE(imgMes->dimensions(2) == 3);

        for (int i = 0; i < 23; i++) {
            REQUIRE(imgMes->data(i) == i);
        }
    }

    SECTION("ImageResult to Message") {
        ImageResultMessage* imgResMes = new ImageResultMessage();

        Util::imageResultToMessage(&imgRes, imgResMes);

        const ImageWrapperMessage* imgMes = &(imgResMes->image());
        REQUIRE(imgMes->filepath() == "src/img");
        REQUIRE(imgMes->dimensions(0) == 10);
        REQUIRE(imgMes->dimensions(1) == 10);
        REQUIRE(imgMes->dimensions(2) == 3);

        REQUIRE(imgResMes->platformdistribution(0).platform().platformid() == "0");
        REQUIRE(imgResMes->platformdistribution(1).platform().platformid() == "1");
        REQUIRE(imgResMes->platformdistribution(0).usage() == .6f);
        REQUIRE(imgResMes->platformdistribution(1).usage() == .4f);

        REQUIRE(imgResMes->classification(0).name() == "dog");
        REQUIRE(imgResMes->classification(0).probability() == .8f);
        REQUIRE(imgResMes->classification(1).name() == "cat");
        REQUIRE(imgResMes->classification(1).probability() == .1f);
        REQUIRE(imgResMes->classification(2).name() == "bird");
        REQUIRE(imgResMes->classification(2).probability() == .05f);
        REQUIRE(imgResMes->classification(3).name() == "house");
        REQUIRE(imgResMes->classification(3).probability() == .025f);
        REQUIRE(imgResMes->classification(4).name() == "garage");
        REQUIRE(imgResMes->classification(4).probability() == .0125f);
    }

    SECTION("Message to Platform") {
        auto *platMes = new PlatformInfoMessage();

        Util::platformInfoToMessage(&cpu, platMes);

        PlatformInfo* plat = Util::messageToPlatformInfo(platMes);
        REQUIRE(plat->getDescription() == "internal CPU");
        REQUIRE(plat->getType() == PlatformType::CPU);
        REQUIRE(plat->getPlatformId() == "0");
        REQUIRE(plat->getPowerConsumption() == 500);
        REQUIRE(plat->getFlops() == 20000);

        platMes = new PlatformInfoMessage();

        Util::platformInfoToMessage(&gpu, platMes);

        plat = Util::messageToPlatformInfo(platMes);
        REQUIRE(plat->getDescription() == "internal GPU");
        REQUIRE(plat->getType() == PlatformType::GPU);
        REQUIRE(plat->getPlatformId() == "1");
        REQUIRE(plat->getPowerConsumption() == 1000);
        REQUIRE(plat->getFlops() == 40000);

        platMes = new PlatformInfoMessage();

        Util::platformInfoToMessage(&fpga, platMes);

        plat = Util::messageToPlatformInfo(platMes);
        REQUIRE(plat->getDescription() == "remote FPGA");
        REQUIRE(plat->getType() == PlatformType::FPGA);
        REQUIRE(plat->getPlatformId() == "2");
        REQUIRE(plat->getPowerConsumption() == 50);
        REQUIRE(plat->getFlops() == 200);

        platMes = new PlatformInfoMessage();

        Util::platformInfoToMessage(&cl_cpu, platMes);

        plat = Util::messageToPlatformInfo(platMes);
        REQUIRE(plat->getDescription() == "CL CPU");
        REQUIRE(plat->getType() == PlatformType::CL_CPU);
        REQUIRE(plat->getPlatformId() == "3");
        REQUIRE(plat->getPowerConsumption() == 100);
        REQUIRE(plat->getFlops() == 400);
    }

    SECTION("Message to NetInfo") {
        auto netMes = new NetInfoMessage();

        Util::netInfoToMessage(&alexNet, netMes);

        NetInfo* alex = Util::messageToNetInfo(netMes);

        REQUIRE(alex->getName() == alexNet.getName());
        REQUIRE(alex->getImageDimension() == alexNet.getImageDimension());
        REQUIRE(alex->getIdentifier() == alexNet.getIdentifier());
    }

    SECTION("Message to ImageWrapper") {
        auto imgMes = new ImageWrapperMessage();

        Util::imageWrapperToMessage(&img, imgMes);

        ImageWrapper* image = Util::messageToImageWrapper(imgMes);

        REQUIRE(image->getData() == img.getData());
        REQUIRE(image->getDimensions() == img.getDimensions());
        REQUIRE(image->getFilepath() == img.getFilepath());
    }

    SECTION("Message to ImageResult") {
        auto imgResMes = new ImageResultMessage();

        Util::imageResultToMessage(&imgRes, imgResMes);

        ImageResult* imageResult = Util::messageToImageResult(imgResMes);

        REQUIRE(imageResult->getCompDistribution()[0].first->getPlatformId() == "0");
        REQUIRE(imageResult->getCompDistribution()[1].first->getPlatformId() == "1");
        REQUIRE(imageResult->getCompDistribution()[0].second == .6f);
        REQUIRE(imageResult->getCompDistribution()[1].second == .4f);
        REQUIRE(imageResult->getCompDistribution().size() == 2);

        REQUIRE(imageResult->getImage().getFilepath() == img.getFilepath());
        REQUIRE(imageResult->getResults()[0].first == "dog");
        REQUIRE(imageResult->getResults()[1].first == "cat");
        REQUIRE(imageResult->getResults()[2].first == "bird");
        REQUIRE(imageResult->getResults()[3].first == "house");
        REQUIRE(imageResult->getResults()[4].first == "garage");
        REQUIRE(imageResult->getResults()[0].second == .8f);
        REQUIRE(imageResult->getResults()[1].second == .1f);
        REQUIRE(imageResult->getResults()[2].second == .05f);
        REQUIRE(imageResult->getResults()[3].second == .025f);
        REQUIRE(imageResult->getResults()[4].second == .0125f);
    }

    SECTION("aggregate computation distribution") {
        auto allResults = std::vector<ImageResult*>();
        allResults.emplace_back(&imgRes);
        allResults.emplace_back(&imgRes2);
        auto newDist = Util::aggregateReplyDistribution(allResults);

        REQUIRE(newDist[0].first->getPlatformId() == "0");
        REQUIRE(newDist[1].first->getPlatformId() == "1");
        REQUIRE(newDist[0].second == .5f);
        REQUIRE(newDist[1].second == .5f);

        allResults.clear();
        allResults.emplace_back(&imgRes2);
        allResults.emplace_back(&imgRes);
        allResults.emplace_back(&imgRes3);


        newDist = Util::aggregateReplyDistribution(allResults);

        REQUIRE(newDist[0].first->getPlatformId() == "1");
        REQUIRE(newDist[1].first->getPlatformId() == "0");
        REQUIRE(newDist[0].second == float(1)/3);
        REQUIRE(newDist[1].second == float(2)/3);
    }
}