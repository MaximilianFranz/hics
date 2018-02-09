//
// Created by pselab on 31.01.18.
//

#include "DetailDialogTest.h"

void DetailDialogTest::initTestCase() {
    std::vector<std::pair<std::string, float>> results;
    std::pair<std::string, float> pair1("Leopard", 0.029);
    std::pair<std::string, float> pair2("Haus", 0.17);
    std::pair<std::string, float> pair3("Tiger", 0.09);
    std::pair<std::string, float> pair4("KIT", 0.016);
    std::pair<std::string, float> pair5("Baukran", 0.684);
    results.push_back(pair1);
    results.push_back(pair2);
    results.push_back(pair3);
    results.push_back(pair4);
    results.push_back(pair5);

    std::vector<int> dimensions{100, 100};
    ImageWrapper imageWrapper(dimensions, "/home/pselab/Dokumente/repo/hics/tests/resources/tf_data_script/dog.png");
    std::vector<std::pair<PlatformInfo*, float>> plat;
    PlatformInfo* info1 = new PlatformInfo("CPU", PlatformType::CPU, "cpu", 100, 4);
    PlatformInfo* info2 = new PlatformInfo("FPGA1", PlatformType::FPGA, "fpga1", 50, 3);
    PlatformInfo* info3 = new PlatformInfo("GPU1", PlatformType::GPU, "gpu1", 34, 55);
    PlatformInfo* info4 = new PlatformInfo("GPU2", PlatformType::GPU, "gpu2", 99, 211);

    plat.push_back(std::pair<PlatformInfo*, float>(info1, 20));
    plat.push_back(std::pair<PlatformInfo*, float>(info2, 10));
    plat.push_back(std::pair<PlatformInfo*, float>(info3, 1));
    plat.push_back(std::pair<PlatformInfo*, float>(info4, 69));

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

void DetailDialogTest::init() {
    detailDialog = new DetailDialog();
}

void DetailDialogTest::cleanup() {
    delete detailDialog;
}

void DetailDialogTest::testInsertDetails() {
    detailDialog->insertDetails(classificationResult);

    QCOMPARE(detailDialog->getComputationTimeQLabel()->text().toStdString(), (std::string)"999");
    QCOMPARE(detailDialog->getPowerConsumptionQLabel()->text().toStdString(), (std::string)"15");
    QCOMPARE(detailDialog->getPlatformUsageQLabel()->text().toStdString(),
             (std::string)"CPU: 20%, FPGA1: 10%, GPU1: 1%, GPU2: 69%");
}

//QTEST_MAIN(DetailDialogTest)