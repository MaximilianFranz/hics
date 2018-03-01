/* Copyright 2018 The HICS Authors
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall
 * be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 */

#include <ctime>
#include <Client.h>
#include <thread>
#include <fstream>
#include <ResourceException.h>

#include "Manager.h"
#include "PreProcessor.h"
#include "PerformanceCalculator.h"
#include "HostPlacer.h"


std::string getHostAdress(std::string hostname);

static std::exception_ptr exceptionptr = nullptr;

void runClassification(ComputationHost* host,
                       std::vector<ImageResult*>& allResults,
                       std::vector<ImageWrapper*> img,
                       NetInfo net,
                       OperationMode mode,
                       std::vector<PlatformInfo*> selecedPlatforms,
                       std::chrono::steady_clock::time_point startTime,
                       int& allTimes) {
    try {
        allResults = host->classify(std::move(img), std::move(net), mode, std::move(selecedPlatforms));
    } catch (...) {
        //TODO: handling
        exceptionptr = std::current_exception();
    }
    std::chrono::steady_clock::time_point timeAfter = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(timeAfter - startTime);
    allTimes = (int)diff.count();
}

Manager::Manager() {

    std::string hostAdress;
    try {
        hostAdress = getHostAdress("fpga");
    } catch (ResourceException& r) {
        //TODO: handling
    }
    ComputationHost* client = new Client("fpga", grpc::CreateChannel(
            hostAdress, grpc::InsecureChannelCredentials()));
    std::cout << getHostAdress("fpga") << std::endl;

    try {
        client->queryNets();
        computationHosts.push_back(client);
    } catch (...) {
        // If the client doesn't respond, it's most likely offline or not reachable
        // TODO: make this more dynamic and allow for clients to show up any time
        delete client;
    }

    ComputationHost* executor = new Executor("local");
    computationHosts.push_back(executor);
   /* ComputationHost* executor1 = new Executor("fpga");
    computationHosts.push_back(executor1);*/
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

ClassificationResult* Manager::update() {

    ClassificationRequest* request = mainWindowHandler->getClassificationRequestState();

    PreProcessor processor = PreProcessor();
    processor.setOutputSize(request->getSelectedNeuralNet().getImageDimension(),
                            request->getSelectedNeuralNet().getImageDimension());

    std::vector<ImageWrapper*> processedImages = processor.processImages(request->getUserImages());

    //Check which platforms of each host were selected
    auto hostPlatforms = std::vector<std::vector<PlatformInfo*>>(computationHosts.size());
    std::vector<PlatformInfo*> selectedPlatforms = request->getSelectedPlatforms();
    for (int i = 0; i < computationHosts.size(); i++) {
        for (auto hostPlatIt : computationHosts[i]->queryPlatform()) {
            auto platIt = std::find_if(selectedPlatforms.begin(), selectedPlatforms.end(),
                                       [&hostPlatIt](PlatformInfo* temp) {
                                           return temp->getPlatformId() == hostPlatIt->getPlatformId();
                                       });
            if (platIt != selectedPlatforms.end()) {
                hostPlatforms[i].push_back(*platIt);
            }
        }
    }

    //Remove a computationHost if none of its Platforms are selected
    std::vector<ComputationHost*> availableHosts = computationHosts;
    for (int i = 0; i < availableHosts.size(); i++) {
        if (hostPlatforms[i].empty()) {
            ComputationHost* currentHost = availableHosts[i];
            availableHosts.erase(std::find_if(availableHosts.begin(),
                                              availableHosts.end(),
                                              [&currentHost](ComputationHost* temp) {
                                                  return temp->getName() == currentHost->getName();
                                              }));
            hostPlatforms.erase(hostPlatforms.begin() + i);
        }
    }
    //TODO ClassifiationRequest, GUI change Platforms to pointer

    std::vector<std::pair<ComputationHost*, int>> hostDistribution =
            HostPlacer::place(availableHosts, (int)processedImages.size(), request->getSelectedOperationMode());

    auto batches = std::vector<std::vector<ImageWrapper*>>(availableHosts.size());
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

    auto allResults = std::vector<std::vector<ImageResult*>>(availableHosts.size());

    std::chrono::steady_clock::time_point time, timeAfter;
    std::chrono::milliseconds diff = std::chrono::milliseconds();

    auto compTime = std::vector<int>(availableHosts.size());

    std::vector<std::thread> classifyThreads;

    for (int i = 0; i < availableHosts.size(); i++) {
        if (!batches[i].empty()) {
            time = std::chrono::steady_clock::now();
            std::thread t(runClassification, availableHosts[i],
                                            std::ref(allResults[i]),
                                            batches[i],
                                            request->getSelectedNeuralNet(),
                                            request->getSelectedOperationMode(),
                                            hostPlatforms[i],
                                            time,
                                            std::ref(compTime[i]));
            classifyThreads.push_back(std::move(t));
        } else {
            //dummy value for hosts that did not compute anything
            allResults[i] = std::vector<ImageResult *>();
            compTime[i] = 1;
        }
    }

    for (int i = 0; i < classifyThreads.size(); i++) {
        classifyThreads[i].join();
    }

    if(exceptionptr) {
        mainWindowHandler->setExceptionptr(exceptionptr);

        //Null exceptionptr for next classification
        exceptionptr = nullptr;
        return nullptr;
    }

    auto hosts = std::vector<PerformanceCalculator::HostInfo*>();

    for (int i = 0; i < availableHosts.size(); i++) {
        auto newHost = new PerformanceCalculator::HostInfo(availableHosts[i]->getName(),
                                                           float(batches[i].size()) / float(processedImages.size()),
                                                           compTime[i]);
        hosts.push_back(newHost);
    }

    std::vector<std::vector<std::pair<PlatformInfo*, float>>> calculateInfo;

    //Add the ComputationDistribution of each host to the calculateInfo
    for (int i = 0; i < batches.size(); i++) {
        if (!batches[i].empty()) {
            std::vector<std::pair<PlatformInfo *, float>> distr = allResults[i].front()->getCompDistribution();
            calculateInfo.push_back(distr);
        } else {
            std::vector<std::pair<PlatformInfo*, float>> distr;
            for (auto hostPlatIt : hostPlatforms[i]) {
                distr.emplace_back(hostPlatIt, 0);
            }
            calculateInfo.push_back(distr);
        }
    }

    PerformanceData performanceData = PerformanceCalculator::calculatePerformance(calculateInfo, hosts);

    std::vector<ImageResult> newResults;

    for (auto hostResults : allResults){
            for (auto singleResult : hostResults) {
                newResults.push_back(*singleResult);
                delete singleResult;
            }
    }

    ClassificationResult* result = new ClassificationResult(newResults, request->getSelectedNeuralNet(), performanceData);

    if(request->getAggregateResults()){
        result->aggregateResults();
    }

    return result;
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

/**
 * Reads the Adress from a computation host specified in the computations.json (only for remote hosts)
 * @param hostname  the name of the computationhost in the .json file
 * @return adress of the computationHost
 */
std::string getHostAdress(std::string hostname) {
    std::ifstream i(RES_DIR "computationHosts.json");
    json computationHostFile;
    i >> computationHostFile;
    json computationHost = computationHostFile["computationHosts"];
    for (auto compHostIt : computationHost) {
        if (compHostIt["name"] == hostname) {
            return compHostIt["host"];
        }
    }
    throw new ResourceException("Host name not found in .json file");
}