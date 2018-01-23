//
// Created by Patrick Deubel on 08.01.18.
//

#include <QApplication>
#include "handler/ui/MainWindow.h"
#include "handler/MainWindowHandler.h"
#include "PerformanceData.h"
#include "ClassificationResult.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    NetInfo net("AlexNet", 224);
//    PlatformInfo platform("CPU", PlatformType::CPU, "id", 100, 4);
//    OperationMode mode(HighPower);

//    std::list<NetInfo> nets;
//    nets.push_back(net);
//    std::list<PlatformInfo> plats;
//    plats.push_back(platform);
//    std::list<OperationMode> modes;
//    modes.push_back(mode);

//    MainWindowHandler handler(nets, plats, modes);


    ResultWidget resultWidget;

    std::vector<std::pair<std::string, float>> results;
    std::pair<std::string, float> pair1("Leopard", 2.9);
    std::pair<std::string, float> pair2("Haus", 17);
    std::pair<std::string, float> pair3("Tiger", 9);
    std::pair<std::string, float> pair4("KIT", 1.6);
    std::pair<std::string, float> pair5("Baukran", 68.4);
    results.push_back(pair1);
    results.push_back(pair2);
    results.push_back(pair3);
    results.push_back(pair4);
    results.push_back(pair5);

    std::vector<int> b(3);
    ImageWrapper imageWrapper(b, "/home/pselab/Bilder/landscape-1843128_960_720.jpg");
    std::vector<std::pair<PlatformInfo, float>> plat;
    PerformanceData performanceData(1, 1, plat);
    ImageResult imgResult(results, imageWrapper);
    std::vector<ImageResult> imgResults;
    imgResults.push_back(imgResult);
    ClassificationResult classificationResult(imgResults, net, performanceData);

    resultWidget.displayResults(classificationResult);
    resultWidget.show();



    return a.exec();
}
