//
// Created by pselab on 27.01.18.
//

#include "StartWidgetTest.h"
#include <handler/ui/StartWidget.h>

void StartWidgetTest::initTestCase() {
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

void StartWidgetTest::init() {
    startWidget = new StartWidget(nets, platforms, modes);
}

void StartWidgetTest::cleanup() {
    delete startWidget;
}

void StartWidgetTest::testConstructor() {

    /*--------------Neural nets--------------------*/

    QCOMPARE(startWidget->getNeuralNetsQComboBox()->itemText(0).toStdString(), (std::string) "AlexNet");

    QCOMPARE(startWidget->getNeuralNetsQComboBox()->itemText(1).toStdString(), (std::string) "GoogLeNet");

    /*--------------Operation Modes----------------*/

    QCOMPARE(startWidget->getOperationModesQComboBox()->itemText(0).toStdString(), (std::string)"High power");

    QCOMPARE(startWidget->getOperationModesQComboBox()->itemText(1).toStdString(), (std::string)"Energy efficient");

    QCOMPARE(startWidget->getOperationModesQComboBox()->itemText(2).toStdString(), (std::string)"Low power");

    /*--------------Platforms---------------------*/

    QCOMPARE(((QCheckBox *) (startWidget->getPlatformsQVBoxLayout()->itemAt(0)->widget()))->text().toStdString(),
             (std::string) "CPU");

    QCOMPARE(((QCheckBox *) (startWidget->getPlatformsQVBoxLayout()->itemAt(1)->widget()))->text().toStdString(),
             (std::string) "FPGA");

    QCOMPARE(((QCheckBox *) (startWidget->getPlatformsQVBoxLayout()->itemAt(2)->widget()))->text().toStdString(),
             (std::string) "Titan XP");
}

void StartWidgetTest::testImageFunctions() {
    startWidget->processInputImageButton();
    //Select 3 images
    QCOMPARE(startWidget->getSelectedImages().size(), (unsigned long) 3);

    QMapIterator<QPair<QImage *, QString>, QHBoxLayout *> it(*(startWidget->getImagesMap()));

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

    QCOMPARE(startWidget->getSelectedPlatforms().at(0).getPlatformId(), (std::string) "cpu");
    QCOMPARE(startWidget->getSelectedPlatforms().at(1).getPlatformId(), (std::string) "fpga");
}

void StartWidgetTest::testSelectedNeuralNet() {
    QCOMPARE(startWidget->getSelectedNeuralNet().getIdentifier(), (std::string) "alexnet");

    QTest::keyClick(startWidget->getNeuralNetsQComboBox(), Qt::Key_Down);

    QCOMPARE(startWidget->getSelectedNeuralNet().getIdentifier(), (std::string) "googlenet");
}

void StartWidgetTest::testSelectedOperationMode() {
    QCOMPARE(startWidget->getSelectedOperationMode(), OperationMode::HighPower);

    QTest::keyClick(startWidget->getOperationModesQComboBox(), Qt::Key_Down);

    QCOMPARE(startWidget->getSelectedOperationMode(), OperationMode::EnergyEfficient);
}

void StartWidgetTest::testIsAggregated() {
    QCOMPARE(startWidget->isAggregated(), false);
    QTest::mouseClick(startWidget->getAggregateResultsQCheckBox(), Qt::LeftButton);
    QCOMPARE(startWidget->isAggregated(), true);
    QTest::mouseClick(startWidget->getAggregateResultsQCheckBox(), Qt::LeftButton);
    QCOMPARE(startWidget->isAggregated(), false);
}

QTEST_MAIN(StartWidgetTest)
