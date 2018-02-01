//
// Created by jallmenroeder on 07/01/18.
//

#pragma once


#include <map>
#include <vector>
#include <QImage>
#include <QString>

#include <NetInfo.h>
#include <PlatformInfo.h>

#include "OperationMode.h"


/**
 * Wraps up the needed data the GUI gathers to run a classification.
 */
class ClassificationRequest {
private:
    std::map<QString, QImage> userImages;   /*!< images to classify mapped with their path as unique key*/
    NetInfo neuralNet;                      /*!< neural net that is used for the classification*/
    std::vector<PlatformInfo> platforms;    /*!< platforms that are used for the computations*/
    OperationMode opMode;                   /*!< specifies if the results should be aggregated*/
    bool aggregate;

public:
    /**
     * Creates a new ClassificationRequest which contains all necessary information for the manager to start the
     * classification.
     * @param neuralNet     neural net which should be used
     * @param platforms     selected platforms
     * @param m             operation mode
     * @param aggregate     if the results should be aggregated
     * @param userImgs      images to classify
     */
    ClassificationRequest(NetInfo neuralNet, std::vector<PlatformInfo> platforms, OperationMode m, bool aggregate,
        std::map<QString, QImage> userImgs);

    /**
     * Adds a new image to the ClassificationRequest. The unique file path is used as the key of the map item.
     * @param str   file path
     * @param img   image to add
     */
    void addUserImage(QString str, QImage img);

    /**
     * Adds a platform to compute classifications.
     * @param platform  platform to add
     */
    void addPlatform(PlatformInfo platform);

    /**
     * Removes an image from the classification, specified by the file path as key.
     * @param str   file path of the image to remove
     */
    void removeUserImage(QString str);


    //SETTER:
    /**
     * Sets the AggregateResults attribute.
     * @param aggregate
     */
    void setAggregateResults(bool aggregate);

    /**
     * Sets the OperationMode attribute.
     * @param mode
     */
    void setSelectedOperationMode(OperationMode mode);

    /**
     * Sets the NeuralNet attribute.
     * @param net
     */
    void setSelectedNeuralNet(NetInfo net);



    //GETTER:
    /**
     * Accesses the map containing the images mapped by their file path.
     * @return      images
     */
    std::map<QString, QImage> getUserImages();

    /**
     * Accesses the list containing the available computation platforms
     * @return      platforms
     */
    std::vector<PlatformInfo*> getSelectedPlatforms();

    /**
     * Accesses the selected operation mode.
     * @return      operation mode as enum
     */
    OperationMode getSelectedOperationMode();

    /**
     * Accesses the selected neural net.
     * @return      neural net
     */
    NetInfo getSelectedNeuralNet();

    /**
     * Returns if the results should be aggregated.
     * @return      bool if aggregated
     */
    bool getAggregateResults();
};
