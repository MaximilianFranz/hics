//
// Created by jallmenroeder on 07/01/18.
//

#ifndef HICS_CLASSIFICATIONREQUEST_H
#define HICS_CLASSIFICATIONREQUEST_H


#include <map>
#include <vector>
#include <QImage>
#include <QString>
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

    ClassificationRequest(NetInfo neuralNet, std::vector<PlatformInfo> platforms, OperationMode m, bool aggregate,
        std::map<QString, QImage> userImgs);

    void addUserImage(QString str, QImage img);
    void addPlatform(PlatformInfo platform);
    void removeUserImage(QString str);

    //Setter
    void setAggregateResults(bool aggregate);
    void setSelectedOperationMode(OperationMode mode);
    void setSelectedNeuralNet(NetInfo net);

    //Getter
    std::map<QString, QImage> getUserImages();
    std::vector<PlatformInfo> getSelectedPlatforms();
    OperationMode getSelectedOperationMode();
    NetInfo getSelectedNeuralNet();
    bool getAggregateResults();
};


#endif //HICS_CLASSIFICATIONREQUEST_H
