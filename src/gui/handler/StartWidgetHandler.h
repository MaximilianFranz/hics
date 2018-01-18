#pragma once

#include <list>
#include <NetInfo.h>
#include <PlatformInfo.h>
#include <OperationMode.h>

class StartWidgetHandler
{
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


};

/*
◦ + processInputImageButton() : void
This method is the slot function to the signal click() on the selectInputImageQPushButton
from the startWidget. It opens a file chooser where the user can select between one
and twenty images. The selected images then get stored and displayed together with
their file path.
◦ + processConfirmDeletionButton() : void
This method is the slot function to the click signal on the confirmDeletionQPushButton,
which will remove all images the user selected for deletion.
◦ + processAbortDeletionButton() : void
This method is the slot function to the signal click() on the abortDeletionQPushButton.
It will abort the deletion of user images by unchecking all deletion check boxes.
23
◦ + getSelectedNeuralNet() : NetInfo
This method gets the selected neural net from startWidget and returns it.
@return: The selected neural net.
◦ + getSelectedPlatforms() : list<PlatformInfo>
This method gets the selected platforms from startWidget and returns it.
@return: The selected platforms.
◦ + getSelectedOperationMode() : OperationMode
This method gets the selected operation mode from startWidget and returns it.
@return: The selected operation mode.
◦ + isAggregated() : bool
This method looks up in startWidget if the user selected to aggregate the results.
@return: true, if the results should be aggregated, false if not.
◦ + getUserImages() : map<QImage, String>
This method returns all selected images by the user as Q
*/
