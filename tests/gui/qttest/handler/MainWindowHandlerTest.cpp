//
// Created by pselab on 30.01.18.
//

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

/*
void StartWidgetTest::classifyButtonClicked() {
    //TODO simulate mouse click on classify button
    QTest::mouseClick(startWidget->getClassificationQPushButton(), Qt::LeftButton);

    ClassificationRequest* request = mainWindowHandler->getClassificationRequestState();
    QCOMPARE(request->getAggregateResults(), false);
    NetInfo net = request->getSelectedNeuralNet();
    QCOMPARE(net.getIdentifier(), nets.front().getIdentifier());
    QCOMPARE(request->getSelectedOperationMode(), modes.front());
    //No platform selected
    //TODO change this when error message implemented
    QCOMPARE(request->getSelectedPlatforms().size(), (unsigned long)0);
}
*/