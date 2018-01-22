#include <NotImplementedException.h>
#include "MainWindowHandler.h"

MainWindowHandler::MainWindowHandler(std::list<NetInfo> &neuralNets, std::list<PlatformInfo> &platforms,
                  std::list<OperationMode> &operationModes) :
startWidget(neuralNets, platforms, operationModes){

    mainWindow.addWidgetToStack(startWidget);
    mainWindow.setCurrentWidget(startWidget);
    //TODO initialze result and detail widget and add them to the stack

    connect(startWidget.getClassificationQPushButton(), SIGNAL(clicked()), this, SLOT(setClassificationRequestState()));
}

void MainWindowHandler::setClassificationRequestState(){
    NetInfo neuralNet = startWidget.getSelectedNeuralNet();
    std::vector<PlatformInfo> platforms = startWidget.getSelectedPlatforms();
    OperationMode m(OperationMode::HighPower); /*!< TODO change this when string mapping is implemented*/
    bool aggregate = startWidget.isAggregated();
    std::map<QString, QImage> userImgs = startWidget.getSelectedImages();

    *(this->classificationRequestState) = ClassificationRequest(neuralNet, platforms, m, aggregate, userImgs);
}

ClassificationRequest* MainWindowHandler::getClassificationRequestState(){
    if(classificationRequestState){
        return classificationRequestState;
    } else {
        return nullptr; //TODO or throw error?
    }
}

void MainWindowHandler::processClassificationResult(const ClassificationResult &classificationResult){
    throw NotImplementedException();
}

void MainWindowHandler::processReturnQPushButton(){
    throw NotImplementedException();
}

void MainWindowHandler::processDetailQPushButton(){
    throw NotImplementedException();
}
