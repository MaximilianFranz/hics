#include <NotImplementedException.h>
#include "MainWindowHandler.h"

MainWindowHandler::MainWindowHandler(std::list<NetInfo> &neuralNets, std::list<PlatformInfo> &platforms,
                  std::list<OperationMode> &operationModes) :
startWidgetHandler(neuralNets, platforms, operationModes){

    mainWindow.addWidgetToStack(startWidgetHandler.getStartWidget());
    mainWindow.setCurrentWidget(startWidgetHandler.getStartWidget());

    //TODO initialze result and detail Handler and add them to the stack
}

void MainWindowHandler::setClassificationRequestState(){
    throw NotImplementedException();
}

ClassificationRequest MainWindowHandler::getClassificationRequestState(){
    throw NotImplementedException();
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
