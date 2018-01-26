#include <NotImplementedException.h>
#include "MainWindowHandler.h"

MainWindowHandler::MainWindowHandler(std::list<NetInfo> &neuralNets, std::list<PlatformInfo> &platforms,
                  std::list<OperationMode> &operationModes) {

    mainWindow = new MainWindow();
    startWidget = new StartWidget(neuralNets, platforms, operationModes, mainWindow);
    resultWidget = new ResultWidget(mainWindow);
    detailDialog = new DetailDialog(mainWindow);

    mainWindow->addWidgetToStack(startWidget);
    mainWindow->addWidgetToStack(resultWidget);

    mainWindow->setCurrentWidget(startWidget);

    connect(startWidget->getClassificationQPushButton(), SIGNAL(clicked()), this, SLOT(setClassificationRequestState()));
    connect(resultWidget->getReturnQPushButton(), SIGNAL(clicked()), this, SLOT(processReturnQPushButton()));
    connect(resultWidget->getDetailsQPushButton(), SIGNAL(clicked()), this, SLOT(processDetailQPushButton()));
    connect(resultWidget, SIGNAL(destroyed()), this, SLOT(processReturnQPushButton())); //TODO Check if this works
}

void MainWindowHandler::setClassificationRequestState(){
    NetInfo neuralNet = startWidget->getSelectedNeuralNet();
    std::vector<PlatformInfo> platforms = startWidget->getSelectedPlatforms();
    OperationMode m(OperationMode::HighPower); /*!< TODO change this when string mapping is implemented*/
    bool aggregate = startWidget->isAggregated();
    std::map<QString, QImage> userImgs = startWidget->getSelectedImages();

    ClassificationRequest request(neuralNet, platforms, m, aggregate, userImgs);
    this->classificationRequestState = &request;

    notify();

    //TODO here maybe display loading screen/bar
}

ClassificationRequest* MainWindowHandler::getClassificationRequestState(){
    if(classificationRequestState){
        return classificationRequestState;
    } else {
        setClassificationRequestState();
        return classificationRequestState;
    }
}

void MainWindowHandler::processClassificationResult(const ClassificationResult &classificationResult){
    resultWidget->displayResults(classificationResult);
    detailDialog->insertDetails(&classificationResult);
    mainWindow->setCurrentWidget(resultWidget);
}

void MainWindowHandler::processReturnQPushButton(){
    mainWindow->setCurrentWidget(startWidget);
    delete resultWidget;
    resultWidget = new ResultWidget(mainWindow);
    delete detailDialog;
    detailDialog = new DetailDialog(mainWindow);
}

void MainWindowHandler::processDetailQPushButton(){
    detailDialog->show();
}
