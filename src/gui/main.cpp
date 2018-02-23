//
// Created by Patrick Deubel on 08.01.18.
//

#include <QApplication>
#include <Manager.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


//    Manager manager;
//    manager.initGUI();


//    std::vector<std::pair<std::string, float>> results;
//    std::pair<std::string, float> pair1("Leopard Leopard Leopard Leopard Leopard Leopard ", 0.029);
//    std::pair<std::string, float> pair2("Haus", 0.17);
//    std::pair<std::string, float> pair3("Tiger", 0.09);
//    std::pair<std::string, float> pair4("KIT", 0.016);
//    std::pair<std::string, float> pair5("Baukran BaukranBaukran Baukran Baukran Baukran Baukran", 0.684);
//    results.push_back(pair1);
//    results.push_back(pair2);
//    results.push_back(pair3);
//    results.push_back(pair4);
//    results.push_back(pair5);
//
//    std::vector<int> dimensions{100, 100};
//    ImageWrapper imageWrapper(dimensions, "/home/pselab/Dokumente/repo/hics/tests/resources/tf_data_script/dog.png");
//    std::vector<std::pair<PlatformInfo*, float>> plat;
//    PlatformInfo* info1 = new PlatformInfo("CPU", PlatformType::CPU, "cpu", 100, 4);
//    PlatformInfo* info2 = new PlatformInfo("FPGA1", PlatformType::FPGA, "fpga1", 50, 3);
//    PlatformInfo* info3 = new PlatformInfo("GPU1", PlatformType::GPU, "gpu1", 34, 55);
//    PlatformInfo* info4 = new PlatformInfo("GPU2", PlatformType::GPU, "gpu2", 99, 211);
//
//    plat.push_back(std::pair<PlatformInfo*, float>(info1, 20));
//    plat.push_back(std::pair<PlatformInfo*, float>(info2, 10));
//    plat.push_back(std::pair<PlatformInfo*, float>(info3, 1));
//    plat.push_back(std::pair<PlatformInfo*, float>(info4, 69));
//
//    PerformanceData performanceData(15, 999, plat);
//    ImageResult imgResult1(results, imageWrapper);
//    ImageResult imgResult2(results, imageWrapper);
//    ImageResult imgResult3(results, imageWrapper);
//    ImageResult imgResult4(results, imageWrapper);
//    ImageResult imgResult5(results, imageWrapper);
//
//    std::vector<ImageResult> imgResults;
//    imgResults.push_back(imgResult1);
//    imgResults.push_back(imgResult2);
//    imgResults.push_back(imgResult3);
//    imgResults.push_back(imgResult4);
//    imgResults.push_back(imgResult5);
//
//    NetInfo alexnet("AlexNet", 227, "alexnet");
//    NetInfo googlenet("GoogLeNet", 300, "googlenet");
//
//    std::list<NetInfo> nets;
//    nets.push_back(alexnet);
//    nets.push_back(googlenet);
//
//    ClassificationResult* classificationResult = new ClassificationResult(imgResults, *(nets.begin()), performanceData);
//    //classificationResult->aggregateResults();
//
//    ResultWidget* result = new ResultWidget();
//    result->displayResults(classificationResult);
//    result->show();
//
//    //delete result;

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

    StartWidget *startWidget = new StartWidget(nets, platforms, modes);
    startWidget->show();
    startWidget->displayProgressBar(5500);
    return a.exec();
}
