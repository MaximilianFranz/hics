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

class StartWidgetTest : public QObject
{

    Q_OBJECT

private:
    std::list<NetInfo> nets;
    std::list<PlatformInfo> platforms;
    std::list<OperationMode> modes;

    MainWindowHandler* mainWindowHandler;
    StartWidget *startWidget;

private slots:

    void initTestCase() {
        NetInfo net("AlexNet", 227, "alex");
        nets.push_back(net);

        PlatformInfo platform("CPU", PlatformType::CPU, "cpu", 100, 5);
        platforms.push_back(platform);

        OperationMode mode = OperationMode::HighPower;
        modes.push_back(mode);

        mainWindowHandler = new MainWindowHandler(nets, platforms, modes);
        startWidget = mainWindowHandler->getStartWidget();
    }

    void classifyButtonClicked();
};

