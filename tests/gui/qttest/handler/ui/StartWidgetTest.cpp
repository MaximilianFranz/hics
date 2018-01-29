//
// Created by pselab on 27.01.18.
//

#include "StartWidgetTest.h"
#include <handler/ui/StartWidget.h>

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

void StartWidgetTest::testSelectedImages() {
/*    startWidget->processInputImageButton();
    //Select 3 images
    QCOMPARE(startWidget->getSelectedImages().size(), (unsigned long)3);*/
}

void StartWidgetTest::testSelectedPlatforms(){
    QTest::mouseClick(startWidget->getPlatformsQVBoxLayout()->itemAt(0)->widget(), Qt::LeftButton);
    QTest::mouseClick(startWidget->getPlatformsQVBoxLayout()->itemAt(1)->widget(), Qt::LeftButton);

    std::list<PlatformInfo>::iterator it;
    it = platforms.begin();
    QCOMPARE(startWidget->getSelectedPlatforms().at(0).getPlatformId(), it->getPlatformId());
    ++it;
    QCOMPARE(startWidget->getSelectedPlatforms().at(1).getPlatformId(), it->getPlatformId());
}

void StartWidgetTest::testSelectedNeuralNet(){
    QTest::keyClick(startWidget->getNeuralNetsQComboBox(), Qt::Key_Down);

    std::list<NetInfo>::iterator it;
    it = nets.begin();
    ++it;
    QCOMPARE(startWidget->getSelectedNeuralNet().getIdentifier(), it->getIdentifier());
}

void StartWidgetTest::testSelectedOperationMode(){
    QTest::keyClick(startWidget->getOperationModesQComboBox(), Qt::Key_Down);

    std::list<OperationMode >::iterator it;
    it = modes.begin();
    ++it;
    //TODO change expected to *it, since the selectedoperationmode method is not yet implemented
    QCOMPARE(startWidget->getSelectedOperationMode(), OperationMode::HighPower);
}

QTEST_MAIN(StartWidgetTest)
