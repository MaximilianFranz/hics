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
        NetInfo alexnet("AlexNet", 227, "alex");
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

        startWidget = new StartWidget(nets, platforms, modes);
    }

    //void classifyButtonClicked();
    void testSelectedPlatforms();
    void testSelectedNeuralNet();
    void testSelectedOperationMode();
    void testSelectedImages();

};

