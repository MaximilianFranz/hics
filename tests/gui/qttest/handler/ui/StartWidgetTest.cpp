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

    std::vector<PlatformInfo>::iterator itActual;
    std::vector<PlatformInfo>::iterator itExpected;
 /*   for(itActual = request->getSelectedPlatforms().begin() && itExpected = platforms.begin(); itActual != request->getSelectedPlatforms().end() && itExpected != platforms.end(); ++itActual && ++itExpected){
        QCOMPARE(itActual->getPlatformId(), )itActual
    }*/
    //QCOMPARE(request->getSelectedPlatforms(), platforms);
}

QTEST_MAIN(StartWidgetTest)
