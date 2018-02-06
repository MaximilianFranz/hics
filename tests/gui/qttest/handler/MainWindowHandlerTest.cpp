//
// Created by pselab on 30.01.18.
//

#include <QtTest/QSignalSpy>
#include <QtWidgets/QLabel>
#include "MainWindowHandlerTest.h"

void MainWindowHandlerTest::initTestCase() {
    NetInfo* alexnet = new NetInfo("AlexNet", 227, "alexnet");
    NetInfo* googlenet = new NetInfo("GoogLeNet", 300, "googlenet");
    nets.push_back(alexnet);
    nets.push_back(googlenet);

    PlatformInfo* cpu = new PlatformInfo("CPU", PlatformType::CPU, "cpu", 100, 5);
    PlatformInfo* fpga = new PlatformInfo("FPGA", PlatformType::FPGA, "fpga", 5, 20);
    PlatformInfo* gpu = new PlatformInfo("Titan XP", PlatformType::FPGA, "titanxp", 250, 100);
    platforms.push_back(cpu);
    platforms.push_back(fpga);
    platforms.push_back(gpu);

    OperationMode mode = OperationMode::HighPower;
    OperationMode mode2 = OperationMode::EnergyEfficient;
    OperationMode mode3 = OperationMode::LowPower;
    modes.push_back(mode);
    modes.push_back(mode2);
    modes.push_back(mode3);
}

void MainWindowHandlerTest::init() {
    mainWindowHandler = new MainWindowHandler(nets, platforms, modes);
}

void MainWindowHandlerTest::cleanup() {
    delete mainWindowHandler;
}

void MainWindowHandlerTest::setUpClassificationResult() {
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

    classificationResult = new ClassificationResult(imgResults, **(nets.begin()), performanceData);
}


void MainWindowHandlerTest::testConstructor() {
    QCOMPARE(mainWindowHandler->getMainWindow()->getMainWindowQStackedWidget()->isVisible(), true);
    QCOMPARE(mainWindowHandler->getMainWindow()->getMainWindowQStackedWidget()->currentWidget(),
             mainWindowHandler->getStartWidget());
    QCOMPARE(mainWindowHandler->getMainWindow()->getMainWindowQStackedWidget()->widget(1),
             mainWindowHandler->getResultWidget());
}

void MainWindowHandlerTest::testStartClassification() {
    QSKIP("testStartClassification works, skipping to avoid QFileSelector popup", SkipSingle);
    mainWindowHandler->getStartWidget()->processInputImageButton();
    QTest::keyClick(mainWindowHandler->getStartWidget()->getNeuralNetsQComboBox(), Qt::Key_Down);
    ((QCheckBox*)(mainWindowHandler->getStartWidget()->getPlatformsQVBoxLayout()->itemAt(1)->widget()))->setChecked(true);

    QTest::mouseClick(mainWindowHandler->getStartWidget()->getClassificationQPushButton(), Qt::LeftButton);

    ClassificationRequest* request = mainWindowHandler->getClassificationRequestState();
    QCOMPARE(request->getAggregateResults(), false);

    QCOMPARE(request->getSelectedNeuralNet().getIdentifier(), (std::string)"googlenet");
    QCOMPARE(request->getSelectedOperationMode(), OperationMode::HighPower); //TODO change this when operation mode implemented
    QCOMPARE(request->getSelectedPlatforms().at(0)->getPlatformId(), (std::string)"fpga");
    QCOMPARE(request->getUserImages().size(), (unsigned long) 1);
}

std::string MainWindowHandlerTest::getLabelFromResultLayout(int layoutPosition, int labelIndex){
    return ((QLabel*)(mainWindowHandler->getResultWidget()->getImagesQGridLayout()
        ->itemAtPosition(0, layoutPosition)->layout()
        ->itemAt(labelIndex)->widget()))->text().toStdString();
}

void MainWindowHandlerTest::testDisplayClassification() {
    setUpClassificationResult();
    mainWindowHandler->processClassificationResult(classificationResult);
    //TODO add getters for result widget and detail dialog
    //Get top result

    QCOMPARE(getLabelFromResultLayout(1, 1), (std::string)"Baukran");

    QCOMPARE(mainWindowHandler->getDetailDialog()->getPowerConsumptionQLabel()->text().toStdString(), (std::string)"15");
    QCOMPARE(mainWindowHandler->getDetailDialog()->getComputationTimeQLabel()->text().toStdString(), (std::string)"999");
    QCOMPARE(mainWindowHandler->getMainWindow()->getMainWindowQStackedWidget()->currentWidget(), mainWindowHandler->getResultWidget());
}

void MainWindowHandlerTest::testReturnButton(){
    QCOMPARE(mainWindowHandler->getMainWindow()->getMainWindowQStackedWidget()->currentWidget(),
             mainWindowHandler->getStartWidget());
    setUpClassificationResult();

    mainWindowHandler->processClassificationResult(classificationResult);

    QCOMPARE(mainWindowHandler->getMainWindow()->getMainWindowQStackedWidget()->currentWidget(),
             mainWindowHandler->getResultWidget());

    QTest::mouseClick(mainWindowHandler->getResultWidget()->getReturnQPushButton(), Qt::LeftButton);

    QCOMPARE(mainWindowHandler->getMainWindow()->getMainWindowQStackedWidget()->currentWidget(),
             mainWindowHandler->getStartWidget());

    QCOMPARE(mainWindowHandler->getResultWidget()->getImagesQGridLayout()->isEmpty(), true);
    QCOMPARE(mainWindowHandler->getDetailDialog()->getComputationTimeQLabel()->text().toStdString(), (std::string)"0");
}

void MainWindowHandlerTest::testDetailButton(){
    QCOMPARE(mainWindowHandler->getDetailDialog()->isVisible(), false);

    QTest::mouseClick(mainWindowHandler->getResultWidget()->getDetailsQPushButton(), Qt::LeftButton);

    QCOMPARE(mainWindowHandler->getDetailDialog()->isVisible(), true);

}
