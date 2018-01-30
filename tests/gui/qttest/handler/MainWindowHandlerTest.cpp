//
// Created by pselab on 30.01.18.
//

#include <QtTest/QSignalSpy>
#include "MainWindowHandlerTest.h"

void MainWindowHandlerTest::initTestCase(){
    NetInfo alexnet("AlexNet", 227, "alexnet");
    NetInfo googlenet("GoogLeNet", 300, "googlenet");
    nets.push_back(alexnet);
    nets.push_back(googlenet);

    PlatformInfo cpu("CPU", PlatformType::CPU, "cpu", 100, 5);
    PlatformInfo fpga("FPGA", PlatformType::FPGA, "fpga", 5, 20);
    PlatformInfo gpu("Titan XP", PlatformType::FPGA, "titanxp", 250, 100);
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

void MainWindowHandlerTest::cleanup(){
    delete mainWindowHandler;
}

void MainWindowHandlerTest::testConstructor() {
    QCOMPARE(mainWindowHandler->getMainWindow()->getMainWindowQStackedWidget()->isVisible(), true);
    QCOMPARE(mainWindowHandler->getMainWindow()->getMainWindowQStackedWidget()->currentWidget(),
             mainWindowHandler->getStartWidget());
    QCOMPARE(mainWindowHandler->getMainWindow()->getMainWindowQStackedWidget()->widget(1),
             mainWindowHandler->getResultWidget());
}

void MainWindowHandlerTest::testStartClassification() {
    mainWindowHandler->getStartWidget()->processInputImageButton();
    QTest::keyClick(mainWindowHandler->getStartWidget()->getNeuralNetsQComboBox(), Qt::Key_Down);
    ((QCheckBox*)(mainWindowHandler->getStartWidget()->getPlatformsQVBoxLayout()->itemAt(1)->widget()))->setChecked(true);

    QTest::mouseClick(mainWindowHandler->getStartWidget()->getClassificationQPushButton(), Qt::LeftButton);

    ClassificationRequest* request = mainWindowHandler->getClassificationRequestState();
    QCOMPARE(request->getAggregateResults(), false);

    QCOMPARE(request->getSelectedNeuralNet().getIdentifier(), (std::string)"googlenet");
    QCOMPARE(request->getSelectedOperationMode(), OperationMode::HighPower); //TODO change this when operation mode implemented
    QCOMPARE(request->getSelectedPlatforms().at(0).getPlatformId(), (std::string)"fpga");
    QCOMPARE(request->getUserImages().size(), (unsigned long) 1);
}


QTEST_MAIN(MainWindowHandlerTest)