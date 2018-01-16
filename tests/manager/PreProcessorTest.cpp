//
// Created by jallmenroeder on 16/01/18.
//

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

    std::vector<ImageWrapper> processedVector = prePro.processImages(map);
    REQUIRE(processedVector[0].getFilepath() == "A");
    REQUIRE(processedVector[1].getFilepath() == "B");

    //REQUIRE_FALSE(img2.pixelColor(0, 0).black() == QColor::Rgb);

SECTION("check scaled image size") {
    ImageWrapper testImg = processedVector[0];

    REQUIRE(testImg.getDimensions()[0] == 3);
    REQUIRE(testImg.getDimensions()[1] == 256);
    REQUIRE(testImg.getDimensions()[2] == 256);


}
SECTION("check filled pixels") {
    ImageWrapper testImg = processedVector[1];

    REQUIRE(testImg.getDimensions()[0] == 3);
    REQUIRE(testImg.getDimensions()[1] == 256);
    REQUIRE(testImg.getDimensions()[2] == 256);
    REQUIRE(testImg.getElement(0, 0, 0) > 0);
    REQUIRE(testImg.getElement(128, 127, 0) > 0);
    REQUIRE_FALSE(testImg.getElement(128, 128, 0) > 0);

}
}