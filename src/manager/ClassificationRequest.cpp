//
// Created by jallmenroeder on 07/01/18.
//

#include "ClassificationRequest.h"


//TODO: functionalities

ClassificationRequest::ClassificationRequest(NetInfo neuralNet, std::vector<PlatformInfo> platforms, OperationMode m,
                                             bool aggregate, std::map<QString, QImage> userImgs) :
        neuralNet(neuralNet), platforms(platforms), opMode(m), aggregate(aggregate), userImages(userImgs) {

}

void ClassificationRequest::addUserImage(QString, QImage) {

}

void ClassificationRequest::removeUserImage(QString) {

}


std::map<QString, QImage> ClassificationRequest::getUserImages() {
    return userImages;
}

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