//
// Created by jallmenroeder on 07/01/18.
//

#include <ctime>
#include <iostream>
#include <Client.h>

#include "Manager.h"
#include "PreProcessor.h"
#include "PerformanceCalculator.h"
#include "HostPlacer.h"

Manager::Manager() {
    ComputationHost* executor = new Executor("local");
    computationHosts.push_back(executor);
    ComputationHost* client = new Client("fpga", grpc::CreateChannel(
            "localhost:50051", grpc::InsecureChannelCredentials()));
    computationHosts.push_back(client);
}

void Manager::initGUI() {
    std::vector<std::vector<NetInfo*>> allNets;
    for (auto host : computationHosts) {
        allNets.push_back(host->queryNets());
    }

    auto nets = netIntersection(allNets);

    auto platforms = std::vector<PlatformInfo*>();
    for (auto host : computationHosts) {
        auto newPlatforms = host->queryPlatform();
        platforms.insert(platforms.end(), newPlatforms.begin(), newPlatforms.end());
    }
    std::vector<OperationMode> modes{OperationMode::HighPower, OperationMode::LowPower, OperationMode::EnergyEfficient};

    mainWindowHandler = new MainWindowHandler(nets, platforms, modes);
    mainWindowHandler->attach(this);
}

void Manager::update() {

    ClassificationRequest* request = mainWindowHandler->getClassificationRequestState();

    PreProcessor processor;
    processor.setOutputSize(request->getSelectedNeuralNet().getImageDimension(),
                            request->getSelectedNeuralNet().getImageDimension());

    std::vector<ImageWrapper*> processedImages = processor.processImages(request->getUserImages());

    std::vector<std::vector<ImageResult*>> allResults;

    std::vector<int> compTime;

    

    //TODO ClassifiationRequest, GUI change Platforms to pointer

    std::vector<std::pair<ComputationHost*, int>> hostDistribution =
            HostPlacer::place(computationHosts, (int)processedImages.size(), request->getSelectedOperationMode());

    auto batches = std::vector<std::vector<ImageWrapper*>>(computationHosts.size());
    int hostIndex = 0;
    int imageIndex = 0;
    for (auto imageIt : processedImages) {
        if (imageIndex < hostDistribution[hostIndex].second) {
            batches[hostIndex].push_back(imageIt);
            imageIndex++;
        } else {
            hostIndex++;
            imageIndex = 0;
            batches[hostIndex].push_back(imageIt);
        }
    }

    std::clock_t time = std::clock();

    for (int i = 0; i < computationHosts.size(); i++) {
        if (batches[i].size() > 0) {
            allResults.push_back(computationHosts[i]->classify(batches[i],
                                                               request->getSelectedNeuralNet(),
                                                               request->getSelectedOperationMode(),
                                                               request->getSelectedPlatforms()));
            compTime.push_back((int)((std::clock() - time)/(CLOCKS_PER_SEC/1000)));
            time = std::clock();
        }
    }



    auto hosts = std::vector<PerformanceCalculator::HostInfo*>();

    for (int i = 0; i < computationHosts.size(); i++) {
        if (batches[i].size() > 0) {
            auto newHost = new PerformanceCalculator::HostInfo(computationHosts[i]->getName(),
                                                               float(batches[i].size()) / float(processedImages.size()),
                                                               compTime[i]);
            hosts.push_back(newHost);
        }
    }

    std::vector<std::vector<std::pair<PlatformInfo*, float>>> calculateInfo;

    for (int i = 0; i < batches.size(); i++) {
        //TODO: wait for implementation of getCompDistribution
        if (batches[i].size() > 0) {
            std::vector<std::pair<PlatformInfo *, float>> distr = allResults[imageIndex].front()->getCompDistribution();
            calculateInfo.push_back(distr);
        }
    }

    PerformanceData performanceData = PerformanceCalculator::calculatePerformance(calculateInfo, hosts);

    std::vector<ImageResult> newResults;

    for (auto hostResults : allResults){
            for (auto singleResult : hostResults) {
                newResults.push_back(*singleResult);
            }
    }

    ClassificationResult* result = new ClassificationResult(newResults, request->getSelectedNeuralNet(), performanceData);

    if(request->getAggregateResults()){
        result->aggregateResults();
    }
    mainWindowHandler->processClassificationResult(result);
}

bool Manager::operator==(const ManagerObserver &managerObserver){
    return this == &managerObserver;
}

std::vector<NetInfo *> Manager::netIntersection(std::vector<std::vector<NetInfo*>> &allNets) {
    auto nets = allNets[0];

    for (auto netIt = allNets.begin() + 1; netIt != allNets.end(); netIt++) {
        auto newNets = netIt.operator*();
        for (auto net : nets) {
            if (std::find_if(newNets.begin(), newNets.end(), [&net](NetInfo* newNet) {
                return newNet->getIdentifier() == net->getIdentifier();
            }) == newNets.end()) {

                nets.erase(std::remove_if(nets.begin(), nets.end(), [&net](NetInfo* newNet) {
                    return newNet->getIdentifier() == net->getIdentifier();
                }));
            }
        }
    }

    return nets;
}
