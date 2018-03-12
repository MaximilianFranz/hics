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

#include <Client.h>
#include <FileHelper.h>
#include <zconf.h>
#include <CommunicationException.h>
#include "ClientServerTest.h"

SCENARIO("Client Server Interaction") {
    SECTION("Classify one image on the client") {
        pid_t pid = fork();
        if (pid == 0) {
            execl(HICS_SERVER "test-server", "test-server", (char *)'\0');
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

            kill(pid, SIGKILL);

            REQUIRE(results[0]->getResults()[0].first == "weasel");

            CommunicationException c(&client, "");

            REQUIRE_THROWS(client.classify({img}, alexnetinfo, OperationMode::EnergyEfficient, platforms), c);

            REQUIRE_THROWS(client.queryPlatform(), c);

            REQUIRE_THROWS(client.queryNets(), c);
        }
    }
}