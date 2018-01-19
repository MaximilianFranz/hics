#include "StartWidgetHandler.h"
#include <NotImplementedException.h>

StartWidgetHandler::StartWidgetHandler(std::list<NetInfo> &neuralNets, std::list<PlatformInfo> &platforms,
                   std::list<OperationMode> &operationModes){

    addNeuralNets(neuralNets);
    startWidget.addPlatforms(platforms);
    startWidget.addOperationModes(operationModes);
}

void StartWidgetHandler::addNeuralNets(std::list<NetInfo> &neuralNets){
    std::list<NetInfo>::iterator it;

    for(it = neuralNets.begin(); it != neuralNets.end(); ++it){
        QString name = QString::fromStdString(it->getName());
        startWidget.addNeuralNets(name);
    }
}

NetInfo StartWidgetHandler::getSelectedNeuralNet(){
    throw NotImplementedException();
}

std::list<PlatformInfo> StartWidgetHandler::getSelectedPlatforms(){
    throw NotImplementedException();
}

OperationMode StartWidgetHandler::getSelectedOperationMode(){
    throw NotImplementedException();
}

bool StartWidgetHandler::isAggregated(){
    throw NotImplementedException();
}

std::map<QImage, std::string> StartWidgetHandler::getUserImages(){
    throw NotImplementedException();
}

void StartWidgetHandler::processInputImageButton(){
    throw NotImplementedException();
}

void StartWidgetHandler::processConfirmDeletionButton(){
    throw NotImplementedException();
}

void StartWidgetHandler::processAbortDeletionButton(){
    throw NotImplementedException();
}
