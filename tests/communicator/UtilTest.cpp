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
    labels.emplace_back("dog", .8);
    labels.emplace_back("cat", .1);
    labels.emplace_back("bird", .05);
    labels.emplace_back("house", .025);
    labels.emplace_back("house", .0125);

    std::vector<std::pair<PlatformInfo, float>> dist;
    dist.emplace_back(cpu, .6);
    dist.emplace_back(gpu, .4);
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

}