#include "StartWidgetHandler.h"
#include <NotImplementedException.h>

StartWidgetHandler::StartWidgetHandler(std::list<NetInfo> &neuralNets, std::list<PlatformInfo> &platforms,
                   std::list<OperationMode> &operationModes){

    addNeuralNets(neuralNets);
    addPlatforms(platforms);
    addOperationModes(operationModes);

    connect(startWidget.getSelectInputImagesQPushButton(), SIGNAL(clicked()), this, SLOT(processInputImageButton()));
}

void StartWidgetHandler::addNeuralNets(std::list<NetInfo> &neuralNets){
    std::list<NetInfo>::iterator it;

    for(it = neuralNets.begin(); it != neuralNets.end(); ++it){
        QString name = QString::fromStdString(it->getName());
        startWidget.addNeuralNet(name);
    }
}

void StartWidgetHandler::addPlatforms(std::list<PlatformInfo> &platforms){
    std::list<PlatformInfo>::iterator it;

    for(it = platforms.begin(); it != platforms.end(); ++it){

        //TODO add platform name when PlatformInfo is implemented.
        startWidget.addPlatform("Platform");
    }
}

void StartWidgetHandler::addOperationModes(std::list<OperationMode> &operationModes){
    std::list<OperationMode>::iterator it;

    for(it = operationModes.begin(); it != operationModes.end(); ++it){
        //TODO add operation mode name when its implemented.
        //QString name = QString::fromStdString(it->);
        startWidget.addOperationMode("Operation mode");
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
    QStringList fileNames = QFileDialog::getOpenFileNames(
                            &startWidget,
                            "Select one or more files to open",
                            "/home",
                            "Images (*.png *.xpm *.jpg)");

    QVector<QImage> images;

    for(int i = 0; i<fileNames.size(); ++i){
        QImage image;
        if(image.load(fileNames.at(i))){
            images.push_back(image);
            startWidget.addInputImage(image);
        }
    }
}

void StartWidgetHandler::processConfirmDeletionButton(){
    throw NotImplementedException();
}

void StartWidgetHandler::processAbortDeletionButton(){
    throw NotImplementedException();
}
