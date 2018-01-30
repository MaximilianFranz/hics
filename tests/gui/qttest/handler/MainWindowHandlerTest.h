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

    std::list<NetInfo> nets;
    std::list<PlatformInfo> platforms;
    std::list<OperationMode> modes;

    MainWindowHandler *mainWindowHandler;

private slots:

    void initTestCase();

    void init();

    void cleanup();

    void testConstructor();

    void testStartClassification();

};

