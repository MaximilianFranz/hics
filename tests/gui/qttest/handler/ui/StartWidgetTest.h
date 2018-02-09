//
// Created by pselab on 27.01.18.
//

#pragma once

#include <QtTest/QtTest>
#include <NetInfo.h>
#include <PlatformInfo.h>
#include <OperationMode.h>
#include <handler/ui/StartWidget.h>
#include <handler/MainWindowHandler.h>

class StartWidgetTest : public QObject {

Q_OBJECT

private:
    std::vector<NetInfo*> nets;
    std::vector<PlatformInfo*> platforms;
    std::vector<OperationMode> modes;

    StartWidget *startWidget;

private slots:

    void initTestCase();

    void init();

    void cleanup();

    //void classifyButtonClicked();

    void testConstructor();

    void testSelectedPlatforms();

    void testSelectedNeuralNet();

    void testSelectedOperationMode();

    void testImageFunctions();

    void testIsAggregated();
};

