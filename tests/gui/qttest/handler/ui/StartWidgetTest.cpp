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

void StartWidgetTest::testConstructor() {
    //TODO test constructor
    //Test available neural nets at startup
    std::list<NetInfo>::iterator it;
    it = nets.begin();
    QCOMPARE(startWidget->getNeuralNetsQComboBox()->itemText(0), it->getName());

    ++it;
    QCOMPARE(startWidget->getNeuralNetsQComboBox()->itemText(1), it->getName());
}

void StartWidgetTest::testImageFunctions() {
    startWidget->processInputImageButton();
    //Select 3 images
    QCOMPARE(startWidget->getSelectedImages().size(), (unsigned long) 3);

    QMapIterator<QImage *, QHBoxLayout *> it(*(startWidget->getImagesMap()));

    it.next();
    ((QCheckBox *) (it.value()->itemAt(0)->widget()))->setChecked(true);

    it.next();
    ((QCheckBox *) (it.value()->itemAt(0)->widget()))->setChecked(true);

    startWidget->processAbortDeletionQPushButton();
    startWidget->processConfirmDeletionButton();
    QCOMPARE(startWidget->getSelectedImages().size(), (unsigned long) 3);

    it.previous();
    ((QCheckBox *) (it.value()->itemAt(0)->widget()))->setChecked(true);

    startWidget->processConfirmDeletionButton();

    QCOMPARE(startWidget->getSelectedImages().size(), (unsigned long) 2);
}

void StartWidgetTest::testSelectedPlatforms() {
    QTest::mouseClick(startWidget->getPlatformsQVBoxLayout()->itemAt(0)->widget(), Qt::LeftButton);
    QTest::mouseClick(startWidget->getPlatformsQVBoxLayout()->itemAt(1)->widget(), Qt::LeftButton);

    std::list<PlatformInfo>::iterator it;
    it = platforms.begin();
    QCOMPARE(startWidget->getSelectedPlatforms().at(0).getPlatformId(), it->getPlatformId());
    ++it;
    QCOMPARE(startWidget->getSelectedPlatforms().at(1).getPlatformId(), it->getPlatformId());
}

void StartWidgetTest::testSelectedNeuralNet() {
    std::list<NetInfo>::iterator it;
    it = nets.begin();
    QCOMPARE(startWidget->getSelectedNeuralNet().getIdentifier(), it->getIdentifier());

    QTest::keyClick(startWidget->getNeuralNetsQComboBox(), Qt::Key_Down);
    ++it;
    QCOMPARE(startWidget->getSelectedNeuralNet().getIdentifier(), it->getIdentifier());
}

void StartWidgetTest::testSelectedOperationMode() {
    std::list<OperationMode>::iterator it;
    it = modes.begin();
    QCOMPARE(startWidget->getSelectedOperationMode(), *it);

    QTest::keyClick(startWidget->getOperationModesQComboBox(), Qt::Key_Down);
    ++it;
    //TODO change expected to *it, since the selectedoperationmode method is not yet implemented
    QCOMPARE(startWidget->getSelectedOperationMode(), OperationMode::HighPower);
}

void StartWidgetTest::testIsAggregated() {
    QCOMPARE(startWidget->isAggregated(), false);
    QTest::mouseClick(startWidget->getAggregateResultsQCheckBox(), Qt::LeftButton);
    QCOMPARE(startWidget->isAggregated(), true);
    QTest::mouseClick(startWidget->getAggregateResultsQCheckBox(), Qt::LeftButton);
    QCOMPARE(startWidget->isAggregated(), false);
}

QTEST_MAIN(StartWidgetTest)
