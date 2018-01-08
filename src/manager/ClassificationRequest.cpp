//
// Created by jallmenroeder on 07/01/18.
//

#include "ClassificationRequest.h"



ClassificationRequest::ClassificationRequest(NetInfo neuralNet, std::vector<PlatformInfo> platforms, OperationMode m,
                                             bool aggregate) : neuralNet(neuralNet), platforms(platforms), opMode(m),
                                                               aggregate(aggregate) {

}


void ClassificationRequest::addUserImage() {

}

void ClassificationRequest::removeUserImage() {

}

//std::map<void, void> ClassificationRequest::getUserImages() {
//    return std::map<void, void>();
//}

void ClassificationRequest::addPlatform(PlatformInfo platform) {
    platforms.push_back(platform);
}

std::vector<PlatformInfo> ClassificationRequest::getSelectedPlatforms() {
    return platforms;
}

void ClassificationRequest::setSelectedOperationMode(OperationMode m) {
    opMode = m;
}

OperationMode ClassificationRequest::getSelectedOperationMode() {
    return opMode;
}

void ClassificationRequest::setSelectedNeuralNet(NetInfo net) {
    neuralNet = net;
}

NetInfo ClassificationRequest::getSelectedNeuralNet() {
    return neuralNet;
}

void ClassificationRequest::setAggregateResults(bool agg) {
    aggregate = agg;
}

bool ClassificationRequest::getAggregateResults() {
    return aggregate;
}
