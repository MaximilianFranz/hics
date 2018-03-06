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

#include <iostream>
#include <sstream>
#include <fstream>

#include <FileHelper.h>

//#include <ClassificationRequest.h>
#include "Client.h"


int main() {
    Client client = Client(grpc::CreateChannel(
            "localhost:50051", grpc::InsecureChannelCredentials()));

    std::vector<NetInfo*> nets = client.queryNets();
    NetInfo alexnetinfo = *nets.at(0);

    std::string img_data_path = TEST_RES_DIR "img_data.txt";

    std::vector<float> image = util::getDataFromFile(img_data_path);

    std::vector<int> imgDim = {3,227,227};
    ImageWrapper *img = new ImageWrapper(imgDim, image, "filepath");

    std::vector<ImageResult*> results;
    std::vector<PlatformInfo*> info_mock;
    results = client.classify({img}, alexnetinfo, OperationMode::EnergyEfficient, info_mock);

    //ClassificationRequest request = ClassificationRequest()

    std::cout << nets[0]->getName() << std::endl;

    std::vector<PlatformInfo*> platforms = client.queryPlatform();

    std::cout << platforms[0]->getDescription() << std::endl;

    std::cout << results[0]->getResults()[0].first << std::endl;
}