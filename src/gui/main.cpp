//
// Created by Patrick Deubel on 08.01.18.
//

#include <QApplication>
#include "handler/ui/MainWindow.h"
#include "handler/MainWindowHandler.h"
#include "PerformanceData.h"
#include "ClassificationResult.h"
#include "handler/ui/DetailDialog.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ResultWidget* resultWidget = new ResultWidget();

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
    PlatformInfo info1("CPU", PlatformType::CPU, "id", 100, 4);
    PlatformInfo info2("FPGA1", PlatformType::FPGA, "id", 50, 3);
    PlatformInfo info3("GPU1", PlatformType::GPU, "id", 34, 55);
    PlatformInfo info4("GPU2", PlatformType::GPU, "id", 99, 211);

    plat.push_back(std::pair<PlatformInfo, float>(info1, 20));
    plat.push_back(std::pair<PlatformInfo, float>(info2, 10));
    plat.push_back(std::pair<PlatformInfo, float>(info3, 1));
    plat.push_back(std::pair<PlatformInfo, float>(info4, 69));

    PerformanceData performanceData(15, 999, plat);
    ImageResult imgResult1(results, imageWrapper);
    ImageResult imgResult2(results, imageWrapper);
    ImageResult imgResult3(results, imageWrapper);
    ImageResult imgResult4(results, imageWrapper);
    ImageResult imgResult5(results, imageWrapper);



    std::vector<ImageResult> imgResults;
    imgResults.push_back(imgResult1);
    imgResults.push_back(imgResult2);
    imgResults.push_back(imgResult3);
    imgResults.push_back(imgResult4);
    imgResults.push_back(imgResult5);

    ClassificationResult classificationResult(imgResults, net, performanceData);

    //resultWidget->displayResults(classificationResult);
    //resultWidget->show();

    DetailDialog* d = new DetailDialog();
    d->insertDetails(&classificationResult);
    d->show();
    return a.exec();
}
