//
// Created by jallmenroeder on 02/02/18.
//

#include "UtilTest.h"
#include "Util.h"
#include "Communicator.grpc.pb.h"
#include "Communicator.pb.h"

SCENARIO("Test") {
    PlatformInfo cpu = PlatformInfo("internal CPU", PlatformType::CPU, "0", 500, 20000);
    PlatformInfo gpu = PlatformInfo("internal GPU", PlatformType::GPU, "1", 1000, 40000);
    PlatformInfo fpga = PlatformInfo("remote FPGA", PlatformType::FPGA, "2", 50, 200);

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
    ImageResult imgRes = ImageResult(labels, dist, img);

    SECTION("PlatformInfo to message") {
        PlatformInfoMessage *platMes = new PlatformInfoMessage();

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
        PlatformInfoMessage *platMes = new PlatformInfoMessage();

        Util::platformInfoToMessage(&cpu, platMes);

        PlatformInfo* plat = Util::messageToPlatformInfo(platMes);
        REQUIRE(plat->getDescription() == "internal CPU");
        REQUIRE(plat->getType() == PlatformType::CPU);
        REQUIRE(plat->getPlatformId() == "0");
        REQUIRE(plat->getPowerConsumption() == 500);
        REQUIRE(plat->getFlops() == 20000);
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

}