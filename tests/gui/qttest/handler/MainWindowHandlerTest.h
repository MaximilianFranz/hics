#pragma once

#include <QtTest/QTest>
#include <QObject>
#include <OperationMode.h>
#include <PlatformInfo.h>
#include <NetInfo.h>
#include <handler/MainWindowHandler.h>

class MainWindowHandlerTest : public QObject {

Q_OBJECT

private:

    std::vector<NetInfo *> nets;
    std::vector<PlatformInfo *> platforms;
    std::vector<OperationMode> modes;

    MainWindowHandler *mainWindowHandler;

    ClassificationResult *classificationResult = nullptr;

    void setUpClassificationResult();

private slots:

    std::string getLabelFromResultLayout(int layoutPosition, int labelIndex);

    void initTestCase();

    void init();

    void cleanup();

    void testConstructor();

    void testStartClassification();

    void testDisplayClassification();

    void testReturnButton();

    void testDetailButton();

};

