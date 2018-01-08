//
// Created by jallmenroeder on 07/01/18.
//

#ifndef HICS_CLASSIFICATIONREQUEST_H
#define HICS_CLASSIFICATIONREQUEST_H


#include <map>
#include <vector>
#include "../platform/PlatformInfo.h"
#include "OperationMode.h"
#include "../netbuilder/NetInfo.h"

class ClassificationRequest {
private:
    NetInfo neuralNet;
    std::vector<PlatformInfo> platforms;
    OperationMode opMode;
    bool aggregate;

public:
    //All needed Methods, Datatypes and parameters still TODO
    ClassificationRequest(NetInfo neuralNet, std::vector<PlatformInfo> platforms, OperationMode m, bool aggregate);

    void addUserImage();
    void removeUserImage();
    //std::map<void, void> getUserImages();
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
