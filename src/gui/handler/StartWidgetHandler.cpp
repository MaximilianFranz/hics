#include "StartWidgetHandler.h"
#include <NotImplementedException.h>

StartWidgetHandler::StartWidgetHandler(std::list<NetInfo> &neuralNets, std::list<PlatformInfo> &platforms,
                   std::list<OperationMode> &operationModes){

    addNeuralNets(neuralNets);
    addPlatforms(platforms);
    addOperationModes(operationModes);

    connect(startWidget.getSelectInputImagesQPushButton(), SIGNAL(clicked()), this, SLOT(processInputImageButton()));
    connect(startWidget.getConfirmDeletionQPushButton(), SIGNAL(clicked()), this, SLOT(processConfirmDeletionButton()));
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

void StartWidgetHandler::clearLayout(QLayout *layout){
    QLayoutItem* item;
    while(item = layout->takeAt(0)){
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if(item->widget()){
            delete item->widget();
        }
        delete item;
    }
}

void StartWidgetHandler::recreateUserImagesLayout(){
    QMap<QImage*, QCheckBox*>::iterator it;

    for(it = images.begin(); it != images.end(); ++it){
        startWidget.addInputImage(it.key(), it.value());
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

    for(int i = 0; i<fileNames.size(); ++i){
        QImage* image = new QImage();
        if(image->load(fileNames.at(i))){
            //TODO delete allocated images in destructor
            QCheckBox* checkBox = startWidget.addInputImage(image);
            images.insert(image, checkBox);
        } else {
            delete image;
        }
    }
}

void StartWidgetHandler::processConfirmDeletionButton(){
    QMap<QImage*, QCheckBox*>::iterator it;
    it = images.begin();

    while(it != images.end()){
        if(it.value()->isChecked()){
            it.value()->setChecked(false);
            it = images.erase(it);
        } else {
            ++it;
        }
    }

    clearLayout(startWidget.getUserImagesQGridLayout());
    //startWidget.resetLayout();
    //recreateUserImagesLayout();
}

void StartWidgetHandler::processAbortDeletionButton(){
    throw NotImplementedException();
}
