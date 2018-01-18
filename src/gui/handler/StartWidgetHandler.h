#pragma once

#include <QObject>
#include <list>
#include <map>
#include <string>
#include <NetInfo.h>
#include <PlatformInfo.h>
#include <OperationMode.h>
#include "ui/StartWidget.h"

class StartWidgetHandler : public QObject {

    Q_OBJECT

private:

    StartWidget startWidget;

public:

    /**
     * @brief StartWidgetHandler
     * @param neuralNets
     * @param platforms
     * @param operationModes
     *
     *
        Constructor which initializes the StartWidgetHandler, creates a startWidget object, initializes
        them and modifies the widgets from startWidget with the given parameters.
        neuralNets: These are the neural nets available in the software.
       platforms: The parameter platforms are the platforms available in the software.
       operationModes: These are the operation modes available.
     *
     *
     */
    StartWidgetHandler(std::list<NetInfo> &neuralNets, std::list<PlatformInfo> &platforms,
                       std::list<OperationMode> &operationModes);

    /**
     * @brief getSelectedNeuralNet
     * @return
     *
     * This method gets the selected neural net from startWidget and returns it.
    @return: The selected neural net.
     */
    NetInfo getSelectedNeuralNet();

    /**
     * @brief getSelectedPlatforms
     * @return
     * This method gets the selected platforms from startWidget and returns it.
@return: The selected platforms.
     */
    std::list<PlatformInfo> getSelectedPlatforms();

    /**
     * @brief getSelectedOperationMode
     * @return
     * This method gets the selected operation mode from startWidget and returns it.
@return: The selected operation mode.
     */
    OperationMode getSelectedOperationMode();

    /**
     * @brief isAggregated
     * @return
     * This method looks up in startWidget if the user selected to aggregate the results.
@return: true, if the results should be aggregated, false if not.
     */
    bool isAggregated();

    /**
     * @brief getUserImages
     * @return
     * This method returns all selected images by the user as QImage together with its file path.
@return: A map of all images with their file paths.
     */
    std::map<QImage, std::string> getUserImages();

public slots:

    /**
     * @brief processInputImageButton
     * This method is the slot function to the signal click() on the selectInputImageQPushButton
    from the startWidget. It opens a file chooser where the user can select between one
    and twenty images. The selected images then get stored and displayed together with
    their file path.
     */
    void processInputImageButton();

    /**
     * @brief processConfirmDeletionButton
     * This method is the slot function to the click signal on the confirmDeletionQPushButton,
     * which will remove all images the user selected for deletion.
     */
    void processConfirmDeletionButton();

    /**
     * @brief processAbortDeletionButton
     * This method is the slot function to the signal click() on the abortDeletionQPushButton.
It will abort the deletion of user images by unchecking all deletion check boxes.
23
     */
    void processAbortDeletionButton();

    StartWidget& getStartWidget(){
        return startWidget;
    }
};
