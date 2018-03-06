#include <handler/MainWindowHandler.h>
#include <QtTest/QSignalSpy>
#include "WorkerThreadTest.h"

void WorkerThreadTest::initTestCase() {
    std::vector<NetInfo*> nets;
    NetInfo* alexnet = new NetInfo("AlexNet", 227, "alexnet");
    NetInfo* googlenet = new NetInfo("GoogLeNet", 300, "googlenet");
    nets.push_back(alexnet);
    nets.push_back(googlenet);

    std::vector<PlatformInfo*> platforms;
    PlatformInfo* cpu = new PlatformInfo("CPU", PlatformType::CPU, "cpu", 100, 5);
    PlatformInfo* fpga = new PlatformInfo("FPGA", PlatformType::FPGA, "fpga", 5, 20);
    PlatformInfo* gpu = new PlatformInfo("Titan XP", PlatformType::FPGA, "titanxp", 250, 100);
    platforms.push_back(cpu);
    platforms.push_back(fpga);
    platforms.push_back(gpu);

    std::vector<OperationMode> modes;
    OperationMode mode = OperationMode::HighPower;
    OperationMode mode2 = OperationMode::EnergyEfficient;
    OperationMode mode3 = OperationMode::LowPower;
    modes.push_back(mode);
    modes.push_back(mode2);
    modes.push_back(mode3);

    mWH = new MainWindowHandler(nets, platforms, modes);
    workerThread = new WorkerThread(mWH);
}

void WorkerThreadTest::testRun() {
    ManagerObserver observer;
    mWH->attach(&observer);

    QSignalSpy spy(workerThread, &WorkerThread::resultReady);

    workerThread->start();
    workerThread->wait();

    QCOMPARE(spy.count(), 1);
}

void WorkerThreadTest::cleanup() {
    delete mWH;
    delete workerThread;
}
