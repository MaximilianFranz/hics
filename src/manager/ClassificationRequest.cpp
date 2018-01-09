//
// Created by jallmenroeder on 07/01/18.
//

#include "ClassificationRequest.h"



ClassificationRequest::ClassificationRequest(NetInfo neuralNet, std::vector<PlatformInfo> platforms, OperationMode m,
                                             bool aggregate, std::map<QString, QImage> userImgs) :
        neuralNet(neuralNet), platforms(platforms), opMode(m), aggregate(aggregate), userImages(userImgs) {

}

void ClassificationRequest::addUserImage(QString str, QImage img) {
    std::pair newUserImg = std::pair(str, img);
    userImages.insert(newUserImg);
}

void ClassificationRequest::addPlatform(PlatformInfo platform) {
    platforms.push_back(platform);
}

void ClassificationRequest::removeUserImage(QString str) {
    userImages.erase(str);
}

void ClassificationRequest::setAggregateResults(bool aggregate) {
    this->aggregate = aggregate;
}

void ClassificationRequest::setSelectedOperationMode(OperationMode mode) {
    opMode = mode;
}

void ClassificationRequest::setSelectedNeuralNet(NetInfo net) {
    neuralNet = net;
}

std::map<QString, QImage> ClassificationRequest::getUserImages() {
    return userImages;
}

std::vector<PlatformInfo> ClassificationRequest::getSelectedPlatforms() {
    return platforms;
}

OperationMode ClassificationRequest::getSelectedOperationMode() {
    return opMode;
}

NetInfo ClassificationRequest::getSelectedNeuralNet() {
    return neuralNet;
}

bool ClassificationRequest::getAggregateResults() {
    return aggregate;
}
