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

#include <QtGui/QColor>
#include "PreProcessorTest.h"

SCENARIO("Preprocess QImage", "[wrapper]") {
    QImage img = QImage(512, 512, QImage::Format_RGB32);
    img.fill(Qt::GlobalColor::black);

    QImage img2 = QImage(1024, 512, QImage::Format_RGB32);
    img2.fill(Qt::GlobalColor::red);

    std::map<QString, QImage> map;
    map.insert(std::pair<QString, QImage>(QString("A"), img));
    map.insert(std::pair<QString, QImage>(QString("B"), img2));

    PreProcessor prePro = PreProcessor();
    prePro.setOutputSize(256, 256);

    std::vector<ImageWrapper*> processedVector = prePro.processImages(map);
    REQUIRE(processedVector[0]->getFilepath() == "A");
    REQUIRE(processedVector[1]->getFilepath() == "B");

    //REQUIRE_FALSE(img2.pixelColor(0, 0).black() == QColor::Rgb);

SECTION("check scaled image size") {
    ImageWrapper testImg = *processedVector[0];

    REQUIRE(testImg.getDimensions()[0] == 3);
    REQUIRE(testImg.getDimensions()[1] == 256);
    REQUIRE(testImg.getDimensions()[2] == 256);
    REQUIRE(testImg.getElement(0, 0, 0) == 0);


}
SECTION("check filled pixels") {
    QColor red = Qt::GlobalColor::red;
    ImageWrapper testImg = *processedVector[1];

    double mean1 = 0;
    //mimick calculation of mean. Just multiplying would not suffice due to floating point precision
    for (long long i = 0; i < 256*128; i++) {
        mean1 += (double)(qRed(red.rgb()))/(256*256);
        mean1 += (double)(qGreen(red.rgb()))/(256*256);
        mean1 += (double)(qBlue(red.rgb()))/(256*256);
    }
    mean1 = mean1 / 3;
    double fCompare1 = (qRed(red.rgb())) - mean1;

    REQUIRE(testImg.getDimensions()[0] == 3);
    REQUIRE(testImg.getDimensions()[1] == 256);
    REQUIRE(testImg.getDimensions()[2] == 256);
    REQUIRE(testImg.getElement(0, 0, 2) == fCompare1);
    REQUIRE(testImg.getElement(127, 128, 2) == fCompare1);
    REQUIRE(testImg.getElement(128, 128, 2) == -mean1);

}
}