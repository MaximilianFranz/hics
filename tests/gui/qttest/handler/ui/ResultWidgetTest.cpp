//
// Created by pselab on 31.01.18.
//

#include <QtWidgets/QLabel>
#include "ResultWidgetTest.h"

void ResultWidgetTest::initTestCase() {
    std::vector<std::pair<std::string, float>> results;
    std::pair<std::string, float> pair1("Leopard", 2.9);
    std::pair<std::string, float> pair2("Haus", 17);
    std::pair<std::string, float> pair3("Tiger", 9);
    std::pair<std::string, float> pair4("KIT", 1.6);
    std::pair<std::string, float> pair5("Baukran", 68.4);
    results.push_back(pair1);
    results.push_back(pair2);
    results.push_back(pair3);
    results.push_back(pair4);
    results.push_back(pair5);

    std::vector<int> dimensions{100, 100};
    ImageWrapper imageWrapper(dimensions, "/home/pselab/Dokumente/repo/hics/tests/resources/tf_data_script/dog.png");
    std::vector<std::pair<PlatformInfo, float>> plat;
    PlatformInfo info1("CPU", PlatformType::CPU, "cpu", 100, 4);
    PlatformInfo info2("FPGA1", PlatformType::FPGA, "fpga1", 50, 3);
    PlatformInfo info3("GPU1", PlatformType::GPU, "gpu1", 34, 55);
    PlatformInfo info4("GPU2", PlatformType::GPU, "gpu2", 99, 211);

    plat.push_back(std::pair<PlatformInfo, float>(info1, 20));
    plat.push_back(std::pair<PlatformInfo, float>(info2, 10));
    plat.push_back(std::pair<PlatformInfo, float>(info3, 1));
    plat.push_back(std::pair<PlatformInfo, float>(info4, 69));

    PerformanceData performanceData(15, 999, plat);
    ImageResult imgResult1(results, imageWrapper);
    ImageResult imgResult2(results, imageWrapper);
    ImageResult imgResult3(results, imageWrapper);
    ImageResult imgResult4(results, imageWrapper);
    ImageResult imgResult5(results, imageWrapper);

    std::vector<ImageResult> imgResults;
    imgResults.push_back(imgResult1);
    imgResults.push_back(imgResult2);
    imgResults.push_back(imgResult3);
    imgResults.push_back(imgResult4);
    imgResults.push_back(imgResult5);

    NetInfo alexnet("AlexNet", 227, "alexnet");
    NetInfo googlenet("GoogLeNet", 300, "googlenet");

    std::list<NetInfo> nets;
    nets.push_back(alexnet);
    nets.push_back(googlenet);

    classificationResult = new ClassificationResult(imgResults, *(nets.begin()), performanceData);
}

void ResultWidgetTest::init() {
    resultWidget = new ResultWidget();
}

void ResultWidgetTest::cleanup() {
    delete resultWidget;
}

std::string ResultWidgetTest::getActualString(int index, int layoutIndex){
    std::string output = ((QLabel *) (resultWidget->getImagesQVBoxLayout()
        ->itemAt(0)->layout()
        ->itemAt(2)->layout()
        ->itemAt(index)->layout()
        ->itemAt(layoutIndex)->widget()))->text().toStdString();

    return output;
}

void ResultWidgetTest::testNotAggregated() {
    resultWidget->displayResults(*classificationResult);
    QCOMPARE(((QLabel *) (resultWidget->getImagesQVBoxLayout()->itemAt(0)
        ->layout()->itemAt(2)
        ->layout()->itemAt(1)
        ->widget()))->text().toStdString(), (std::string) "Baukran");

//    QCOMPARE(((QLabel *) (resultWidget->getImagesQVBoxLayout()
//        ->itemAt(0)->layout()
//        ->itemAt(2)->layout()
//        ->itemAt(2)->layout()
//        ->itemAt(0)->widget()))->text().toStdString(), (std::string) "Baukran");
//    QCOMPARE(((QLabel *) (resultWidget->getImagesQVBoxLayout()
//        ->itemAt(0)->layout()
//        ->itemAt(2)->layout()
//        ->itemAt(2)->layout()
//        ->itemAt(1)->widget()))->text().toStdString(), (std::string) "68.4%");
//
//    QCOMPARE(((QLabel *) (resultWidget->getImagesQVBoxLayout()
//        ->itemAt(0)->layout()
//        ->itemAt(2)->layout()
//        ->itemAt(6)->layout()
//        ->itemAt(0)->widget()))->text().toStdString(), (std::string) "KIT");
//    QCOMPARE(((QLabel *) (resultWidget->getImagesQVBoxLayout()
//        ->itemAt(0)->layout()
//        ->itemAt(2)->layout()
//        ->itemAt(6)->layout()
//        ->itemAt(1)->widget()))->text().toStdString(), (std::string) "1.6%");

    QCOMPARE(getActualString(2, 0), (std::string)"Baukran");
    QCOMPARE(getActualString(2, 1), (std::string)"68.4%");

    QCOMPARE(getActualString(3, 0), (std::string)"Haus");
    QCOMPARE(getActualString(3, 1), (std::string)"17%");

    QCOMPARE(getActualString(4, 0), (std::string)"Tiger");
    QCOMPARE(getActualString(4, 1), (std::string)"9%");

    QCOMPARE(getActualString(5, 0), (std::string)"Leopard");
    QCOMPARE(getActualString(5, 1), (std::string)"2.9%");

    QCOMPARE(getActualString(6, 0), (std::string)"KIT");
    QCOMPARE(getActualString(6, 1), (std::string)"1.6%");

    QCOMPARE(resultWidget->getImagesQVBoxLayout()->count(), 6);
}

QTEST_MAIN(ResultWidgetTest)