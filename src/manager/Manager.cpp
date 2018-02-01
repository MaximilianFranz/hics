//
// Created by jallmenroeder on 07/01/18.
//

#include "Manager.h"
#include "PreProcessor.h"

Manager::Manager(){
    executor = new Executor("standard");
}

void Manager::initGUI(){
    auto nets = executor->queryNets();
    auto platforms = executor->queryPlatform();
    std::list<OperationMode> modes{OperationMode::HighPower, OperationMode::LowPower, OperationMode::EnergyEfficient};

    //TODO change list to vector
    std::list<NetInfo*> newNets(nets.begin(), nets.end());
    std::list<PlatformInfo*> newPlats(platforms.begin(), platforms.end());

    mainWindowHandler = new MainWindowHandler(newNets, newPlats, modes);
    mainWindowHandler->attach(this);
}

void Manager::update(){
    ClassificationRequest* request = mainWindowHandler->getClassificationRequestState();
    PreProcessor processor;
    processor.setOutputSize(request->getSelectedNeuralNet().getImageDimension(),
                            request->getSelectedNeuralNet().getImageDimension());

    std::vector<ImageWrapper*> processedImages = processor.processImages(request->getUserImages());

    //TODO ClassifiationRequest, GUI change Platforms to pointer

    auto imageResults = executor->classify(processedImages,
                                           request->getSelectedNeuralNet(),
                                           request->getSelectedOperationMode(),
                                           request->getSelectedPlatforms());

    //TODO delete this shit
    std::vector<std::pair<PlatformInfo, float>> plat;
    PlatformInfo info1("CPU", PlatformType::CPU, "cpu", 100, 4);
    PlatformInfo info2("FPGA1", PlatformType::FPGA, "fpga1", 50, 3);
    PlatformInfo info3("GPU1", PlatformType::GPU, "gpu1", 34, 55);
    PlatformInfo info4("GPU2", PlatformType::GPU, "gpu2", 99, 211);

    plat.push_back(std::pair<PlatformInfo, float>(info1, 20));
    plat.push_back(std::pair<PlatformInfo, float>(info2, 10));
    plat.push_back(std::pair<PlatformInfo, float>(info3, 1));
    plat.push_back(std::pair<PlatformInfo, float>(info4, 69));

    PerformanceData performanceData(15, 999, plat);

    std::vector<ImageResult> newResults;

    for(auto i : imageResults){
        newResults.push_back(*i);
    }

    ClassificationResult* result = new ClassificationResult(newResults, request->getSelectedNeuralNet(), performanceData);

    mainWindowHandler->processClassificationResult(*result);
}

bool Manager::operator==(const ManagerObserver &managerObserver){
    return this == &managerObserver;
}