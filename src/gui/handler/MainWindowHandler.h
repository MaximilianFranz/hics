#pragma once

#include <list>
#include <QObject>
#include <NetInfo.h>
#include <PlatformInfo.h>
#include <OperationMode.h>
#include <ClassificationRequest.h>
#include <ClassificationResult.h>

#include "MainWindowSubject.h"
#include "StartWidgetHandler.h"
#include "ResultWidgetHandler.h"
#include "DetailDialogHandler.h"
#include "ui/MainWindow.h"

//TODO detailed comments when methods are implemented

/**
 * @class   MainWindowHandler
 *
 * @brief   MainWindowHandler is used as the main controller of the GUI. It is facade to the Manager and abstracts
 *          away the GUI.
 *
 * MainWindowHandler stores a StartWidgetHandler, ResultWidgetHandler and DetailDialogHanlder as well as the
 * MainWIndow. It delegates actions to these Handler's which then use their QWidget's/QDialog to display the user
 * interface.
 * MainWindowHandler is inherited from MainWindowSubject which means that it is a concrete subject in the observer
 * design pattern. Its state is a ClassificationRequest, the classificationRequestState which observers can retrieve
 * when they are notified.
 * The two methods processReturnQPushButton() and processDetailQPushButton() are connected to the returnQPushButton
 * and detailsQPushButton from resultWidget, since a click on them means that the displayed widget need to be changed.
 *
 * @author  Patrick Deubel
 * @date    17.01.2018
 *
 */
class MainWindowHandler : public QObject, MainWindowSubject{

    Q_OBJECT

signals:

    void emitSignal();

private:

    MainWindow mainWindow;

    StartWidgetHandler startWidgetHandler;
    ResultWidgetHandler resultWidgetHandler;
    DetailDialogHandler detailDialogHandler;

    //ClassificationRequest classificationRequestState;
    //TODO properly initialize this in the constructor.

public:

    MainWindowHandler(){

        connect(this, SIGNAL(emitSignal()), &mainWindow, SLOT(createButton()));
        emit emitSignal();
    }

     /**
     * @brief This constructor initializes the GUI with the needed information on available data.
     *
     * The constructor gets the available neural nets, platforms and operation modes which will be displayed after
     * the GUI is constructed.
     * TODO more info
     *
     * @param neuralNets the available neural nets in the software
     * @param platforms the available platforms in the software
     * @param operationModes the available operation modes in the software
     */
    MainWindowHandler(const std::list<NetInfo> &neuralNets, const std::list<PlatformInfo> &platforms,
                      const std::list<OperationMode> &operationModes);

    /**
     * @brief setClassificationRequestState will gather the needed data for a ClassificationRequest and overwrite
     *        classificationRequestState with the latest data.
     */
    void setClassificationRequestState();

    /**
     * @brief getClassificationRequestState returns the classificationRequest state attribute.
     * @return classificationRequestState
     */
    ClassificationRequest getClassificationRequestState();

    /**
     * @brief processClassificationResult will display the provided data in the ClassificationResult in the GUI.
     * @param classificationResult contains the classification result and details which shall be displayed
     */
    void processClassificationResult(const ClassificationResult &classificationResult);

    //TODO here could be the displayErrorMessage(Exception e) method

    /**
     * @brief processReturnQPushButton will display the startWidget with the same content as before the classification.
     */
    void processReturnQPushButton();

    /**
     * @brief processDetailQPushButton will open the detailDialog which has the classification details.
     *
     * The DetailDialogHandler will be used to get the detailDialog which has been initialized in the
     * processClassificationResult method.
     */
    void processDetailQPushButton();
};
