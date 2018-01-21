#include "StartWidgetHandler.h"
#include <NotImplementedException.h>

StartWidgetHandler::StartWidgetHandler(std::list<NetInfo> &neuralNets, std::list<PlatformInfo> &platforms,
                   std::list<OperationMode> &operationModes):
startWidget(neuralNets, platforms, operationModes){

    //addNeuralNets(neuralNets);
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
            QHBoxLayout* layout = startWidget.addInputImage(image);
            images.insert(image, layout);
        } else {
            delete image;
        }
    }
}

void StartWidgetHandler::processConfirmDeletionButton(){

    QMapIterator<QImage*, QHBoxLayout*> it(images);
    while (it.hasNext()) {
        it.next();
        QCheckBox* checkBox;
        //TODO maybe check for it.value()->itemAt(0) if this is a valid pointer
        if(checkBox = (QCheckBox*)(it.value()->itemAt(0)->widget())){
                if(checkBox->isChecked()){
                    clearLayout(it.value());
                    QHBoxLayout* tempLayout = it.value();
                    QImage* tempImage = it.key();
                    images.remove(it.key());
                    delete tempLayout;
                    delete tempImage;
                }
        }
    }
}

void StartWidgetHandler::processAbortDeletionButton(){
    throw NotImplementedException();
}
