//
// Created by jallmenroeder on 06/03/18.
//

#include <Client.h>
#include <FileHelper.h>
#include <zconf.h>
#include <CommunicationException.h>
#include "ClientServerTest.h"

SCENARIO("Client Server Interaction") {
    SECTION("Classify one image on the client") {
        pid_t pid = fork();
        if (pid == 0) {
            execl(HICS_SERVER "test-server", NULL);
        } else {
            sleep(1);
            Client client = Client(grpc::CreateChannel(
                    "localhost:50052", grpc::InsecureChannelCredentials()));

            std::vector<NetInfo *> nets = client.queryNets();
            std::vector<PlatformInfo *> platforms = client.queryPlatform();
            NetInfo alexnetinfo = *nets.at(0);

            std::string img_data_path = TEST_RES_DIR "img_data.txt";

            std::vector<float> image = util::getDataFromFile(img_data_path);

            std::vector<int> imgDim = {3, 227, 227};
            ImageWrapper *img = new ImageWrapper(imgDim, image, "filepath");

            std::vector<ImageResult *> results;
            results = client.classify({img}, alexnetinfo, OperationMode::EnergyEfficient, platforms);

            kill(pid, SIGTERM);

            REQUIRE(results[0]->getResults()[0].first == "weasel");

            CommunicationException c(&client, "");

            REQUIRE_THROWS(client.classify({img}, alexnetinfo, OperationMode::EnergyEfficient, platforms), c);

            REQUIRE_THROWS(client.queryPlatform(), c);

            REQUIRE_THROWS(client.queryNets(), c);
        }
    }
}