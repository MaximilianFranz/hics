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

#include <QtTest/QSignalSpy>
#include <QtWidgets/QLabel>
#include <QMessageBox>
#include <iostream>
#include <memory>
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

    plat.push_back(std::pair<PlatformInfo*, float>(info1, 0.2));
    plat.push_back(std::pair<PlatformInfo*, float>(info2, 0.1));
    plat.push_back(std::pair<PlatformInfo*, float>(info3, 0.01));
    plat.push_back(std::pair<PlatformInfo*, float>(info4, 0.69));

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
    //QSKIP("testStartClassification works, skipping to avoid QFileSelector popup", SkipSingle);
    QMessageBox box;
    box.setText("Select one image");
    box.show();

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

void MainWindowHandlerTest::testDisplayClassification() {
    setUpClassificationResult();
    mainWindowHandler->processClassificationResult(classificationResult);

    //Get top result
    QCOMPARE(mainWindowHandler->getResultWidget()->getResultDisplays()[0]->topResult.first, (std::string)"Baukran");

    QCOMPARE(mainWindowHandler->getDetailDialog()->getPowerConsumptionQLabel()->text().toStdString(), (std::string)"15 Ws");
    QCOMPARE(mainWindowHandler->getDetailDialog()->getComputationTimeQLabel()->text().toStdString(), (std::string)"999 ms");
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

void MainWindowHandlerTest::testUpdatePlatforms() {
    QCOMPARE(mainWindowHandler->getStartWidget()->getPlatformsQVBoxLayout()->count(), 3);

    auto newPlatforms = new std::vector<PlatformInfo *>;
    newPlatforms->push_back(platforms[0]);
    newPlatforms->push_back(platforms[1]);
    std::shared_ptr<std::vector<PlatformInfo *>> pointer(newPlatforms);
    mainWindowHandler->updatePlatforms(pointer);
    mainWindowHandler->processClassificationResult(nullptr);

    QCOMPARE(mainWindowHandler->getStartWidget()->getPlatformsQVBoxLayout()->count(), 2);
}

void MainWindowHandlerTest::testAbortClassification() {
    QCOMPARE(mainWindowHandler->isClassificationAborted(), false);
    QTest::mouseClick(mainWindowHandler->getStartWidget()->getCancelProgressButton(), Qt::LeftButton);
    QCOMPARE(mainWindowHandler->isClassificationAborted(), true);
}

void MainWindowHandlerTest::testFalseClassification() {
    QCOMPARE(mainWindowHandler->getMainWindow()->getMainWindowQStackedWidget()->currentWidget(),
             mainWindowHandler->getStartWidget());
    mainWindowHandler->processClassificationResult(nullptr);

    //No Exception has been thrown but a nullptr is the parameter so just the progress screen is resetted.
    QCOMPARE(mainWindowHandler->getMainWindow()->getMainWindowQStackedWidget()->currentWidget(),
             mainWindowHandler->getStartWidget());
    std::exception_ptr exceptionptr = nullptr;

    try {
        throw std::logic_error("Sample error");
    } catch (std::exception &e) {
        exceptionptr = std::current_exception();
    }

    mainWindowHandler->setExceptionptr(exceptionptr);
    mainWindowHandler->processClassificationResult(nullptr);

    //Should now display an error message

    //Since no real classification has been processed startWidget is still active
    QCOMPARE(mainWindowHandler->getMainWindow()->getMainWindowQStackedWidget()->currentWidget(),
             mainWindowHandler->getStartWidget());
}
