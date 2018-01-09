//
// Created by jallmenroeder on 07/01/18.
//

#ifndef HICS_CLASSIFICATIONREQUEST_H
#define HICS_CLASSIFICATIONREQUEST_H


#include <map>
#include <vector>
#include <QtGui/QImage>
#include <QtCore/QString>
#include "PlatformInfo.h"
#include "OperationMode.h"
#include "NetInfo.h"

class ClassificationRequest {
private:
    std::map<QString, QImage> userImages;
    NetInfo neuralNet;
    std::vector<PlatformInfo> platforms;
    OperationMode opMode;
    bool aggregate;

public:
    //All needed Methods, Datatypes and parameters still TODO
    ClassificationRequest(NetInfo neuralNet, std::vector<PlatformInfo> platforms, OperationMode m, bool aggregate,
        std::map<QString, QImage> userImgs);

    void addUserImage(QString, QImage);
    void removeUserImage(QString);
    std::map<QString, QImage> getUserImages();
    void addPlatform(PlatformInfo platform);
    std::vector<PlatformInfo> getSelectedPlatforms();
    void setSelectedOperationMode(OperationMode mode);
    OperationMode getSelectedOperationMode();
    void setSelectedNeuralNet(NetInfo net);
    NetInfo getSelectedNeuralNet();
    void setAggregateResults(bool aggregate);
    bool getAggregateResults();
};


#endif //HICS_CLASSIFICATIONREQUEST_H
