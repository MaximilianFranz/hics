//
// Created by jallmenroeder on 07/01/18.
//

#include "ClassificationRequest.h"



ClassificationRequest::ClassificationRequest(NetInfo neuralNet, std::vector<PlatformInfo> platforms, OperationMode m,
                                             bool aggregate, std::map<QString, QImage> userImgs) :
        neuralNet(neuralNet), platforms(std::move(platforms)), opMode(m), aggregate(aggregate), userImages(std::move(userImgs)) {

}



void ClassificationRequest::addUserImage(QString str, QImage img) {
    std::pair <QString, QImage> newImg(str, img);
    userImages.insert(newImg);
}

void ClassificationRequest::addPlatform(PlatformInfo platform) {
    platforms.push_back(platform);
}

void ClassificationRequest::removeUserImage(QString str) {
    userImages.erase(str);
}



//-----------------SETTER-----------------------------

void ClassificationRequest::setAggregateResults(bool aggregate) {
    this->aggregate = aggregate;
}

void ClassificationRequest::setSelectedOperationMode(OperationMode mode) {
    opMode = mode;
}

void ClassificationRequest::setSelectedNeuralNet(NetInfo net) {
    neuralNet = net;
}


//-----------------GETTER----------------------------

std::map<QString, QImage> ClassificationRequest::getUserImages() {
    return userImages;
}

std::vector<PlatformInfo*> ClassificationRequest::getSelectedPlatforms() {
    std::vector<PlatformInfo*> output;
    std::vector<PlatformInfo>::iterator it;

    for(it = platforms.begin(); it != platforms.end(); ++it){
        output.push_back(&(*it));
    }
    return output;
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
