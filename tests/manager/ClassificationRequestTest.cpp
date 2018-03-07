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

#include <NetInfo.h>
#include <PlatformInfo.h>
#include <OperationMode.h>
#include <QtGui/QImage>
#include <ClassificationRequest.h>
#include "ClassificationRequestTest.h"

SCENARIO("Test basic functions") {
    NetInfo alex = NetInfo("alexNet", 5, "Alex Net");
    NetInfo google = NetInfo("google", 6, "GoogLeNet");
    PlatformInfo cpu = PlatformInfo("cpu", PlatformType::CPU, "0", 100, 200);
    PlatformInfo gpu = PlatformInfo("gpu", PlatformType::GPU, "1", 300, 400);

    OperationMode ee = OperationMode::EnergyEfficient;
    OperationMode lp = OperationMode::LowPower;

    QImage img1 = QImage(100, 200, QImage::Format_RGB32);
    QImage img2 = QImage(300, 400, QImage::Format_RGB16);

    QString img1str = "img1";
    QString img2str = "img2";

    std::vector<PlatformInfo> plats = {cpu};
    std::map<QString, QImage> imgs = {std::pair<QString, QImage>(img1str, img1)};

    SECTION("Constructor") {
        auto request = ClassificationRequest(alex, plats, ee, false, imgs);
        REQUIRE(request.getSelectedNeuralNet().getName() == alex.getName());
        REQUIRE(request.getSelectedPlatforms()[0]->getPlatformId() == "0");
        REQUIRE(request.getSelectedOperationMode() == OperationMode::EnergyEfficient);
        REQUIRE_FALSE(request.getAggregateResults());
        REQUIRE(request.getUserImages().at("img1").width() == 100);
    }

    SECTION("Setter") {
        auto request = ClassificationRequest(alex, plats, ee, false, imgs);
        request.setAggregateResults(true);
        request.setSelectedNeuralNet(google);
        request.setSelectedOperationMode(lp);

        REQUIRE(request.getAggregateResults());
        REQUIRE(request.getSelectedNeuralNet().getName() == google.getName());
        REQUIRE(request.getSelectedOperationMode() == lp);
    }

    SECTION("add and remove") {
        auto request = ClassificationRequest(alex, plats, ee, false, imgs);
        request.addPlatform(gpu);
        request.addUserImage(img2str, img2);
        REQUIRE(request.getSelectedPlatforms().size() == 2);
        REQUIRE(request.getSelectedPlatforms()[1]->getPlatformId() == gpu.getPlatformId());
        REQUIRE(request.getUserImages().size() == 2);
        REQUIRE(request.getUserImages().at(img2str).width() == 300);

        request.removeUserImage(img1str);

        REQUIRE(request.getUserImages().size() == 1);
        REQUIRE(request.getUserImages().at(img2str).width() == 300);
        REQUIRE_THROWS(request.getUserImages().at(img1str));
    }
}