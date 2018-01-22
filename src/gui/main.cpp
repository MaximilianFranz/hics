//
// Created by Patrick Deubel on 08.01.18.
//

#include <QApplication>
#include "handler/ui/MainWindow.h"
#include "handler/MainWindowHandler.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    NetInfo net("AlexNet", 224);
    PlatformInfo platform("CPU", PlatformType::CPU, "id", 100, 4);
    OperationMode mode(HighPower);

    std::list<NetInfo> nets;
    nets.push_back(net);
    std::list<PlatformInfo> plats;
    plats.push_back(platform);
    std::list<OperationMode> modes;
    modes.push_back(mode);

    MainWindowHandler handler(nets, plats, modes);





    return a.exec();
}
