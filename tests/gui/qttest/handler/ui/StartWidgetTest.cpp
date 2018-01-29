//
// Created by pselab on 27.01.18.
//

#include "StartWidgetTest.h"
#include <handler/ui/StartWidget.h>

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

void StartWidgetTest::addInputImage() {
    startWidget->processInputImageButton();
    //Select 3 images
    QTest::mouseClick(startWidget->getClassificationQPushButton(), Qt::LeftButton);
    ClassificationRequest* request = mainWindowHandler->getClassificationRequestState();
    QCOMPARE(request->getUserImages().size(), (unsigned long)3);
}

void StartWidgetTest::changeOptions() {
    NetInfo googlenet("GoogLeNet", 300, "googlenet");
    PlatformInfo fgpa("FPGA", PlatformType::FPGA, "fpga", 5, 20);
    PlatformInfo gpu("Titan XP", PlatformType::FPGA, "titanxp", 250, 100);
    OperationMode mode2 = OperationMode::EnergyEfficient;
    OperationMode mode3 = OperationMode::LowPower;

    nets.push_back(googlenet);
    platforms.push_back(fgpa);
    platforms.push_back(gpu);
    modes.push_back(mode2);
    modes.push_back(mode3);

    delete mainWindowHandler;
    delete startWidget;
    mainWindowHandler = new MainWindowHandler(nets, platforms, modes);
    startWidget = mainWindowHandler->getStartWidget();

    
}

QTEST_MAIN(StartWidgetTest)
