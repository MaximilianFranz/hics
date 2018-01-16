#pragma once

#include <list>
#include <NetInfo.h>
#include <PlatformInfo.h>
#include <OperationMode.h>
#include <ClassificationRequest.h>

#include "MainWindowSubject.h"
#include "StartWidgetHandler.h"
#include "ResultWidgetHandler.h"
#include "DetailDialogHandler.h"
#include "ui/MainWindow.h"


class MainWindowHandler : public MainWindowSubject{

private:

    MainWindow mainWindow;
    StartWidgetHandler startWidgetHandler;
    ResultWidgetHandler resultWidgetHandler;
    DetailDialogHandler detailDialogHandler;

public:
    MainWindowHandler(const std::list<NetInfo> &neuralNets, const std::list<PlatformInfo> &platforms,
                      const std::list<OperationMode> &operationModes);

    void setClassificationRequestState();

    ClassificationRequest getClassificationRequestState();

    void processClassificationResult(const ClassificationResult &classificationResult);

    //TODO here could be the displayErrorMessage(Exception e) method

    void processReturnQPushButton();

    void processDetailQPushButton();
};
