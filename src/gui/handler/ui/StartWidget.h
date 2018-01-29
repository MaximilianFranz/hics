#pragma once

#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QHBoxLayout>
#include <QImage>
#include <QMap>
#include <list>
#include <map>
#include <vector>
#include <NetInfo.h>
#include <PlatformInfo.h>
#include <OperationMode.h>
#include <QtWidgets/QComboBox>

namespace Ui {
class StartWidget;
}

/**
 * @class StartWidget
 *
 * @brief The StartWidget class is a custom QWidget used to display the starting page of the GUI.
 *
 * StartWidget inherits QWidget and is therefore a custom QWidget. It defines the UI of the page as well as methods
 * to get selected data by the user. When created with its constructor, the supplied data gets displayed and the
 * user can select input images, neural nets, platforms, operation modes and if he wants to aggregate the results or
 * not.
 *
 * @author Patrick Deubel
 */
class StartWidget : public QWidget
{
    Q_OBJECT

public:

    /**
     * @brief The constructor takes the available neural nets, platforms and operation modes and displays them.
     *
     * The constructor initializes the UI with the given parameters and connects the selectInputImagesQPushButton,
     * confirmDeletionQPushButton and abortDeletionQPushButton to its slots.
     *
     * @param neuralNets are the available neural nets in the software
     * @param platforms are the available platforms which can be used for the computing
     * @param operationModes are the available operation modes
     * @param parent is a possible parent widget
     */
    explicit StartWidget(std::list<NetInfo> &neuralNets, std::list<PlatformInfo> &platforms,
                                      std::list<OperationMode> &operationModes, QWidget *parent = 0);

    /**
     * The destructor to delete all allocated memory on the heap.
     */
    ~StartWidget();

    /**
     * @brief getSelectedNeuralNet returns the selected neural net by the user.
     * @return the selected neural net
     */
    NetInfo getSelectedNeuralNet();

    /**
     * @brief getSelectedPlatforms returns the selected platforms by the user.
     * @return the selected platforms
     */
    std::vector<PlatformInfo> getSelectedPlatforms();

    /**
     * @brief getSelectedImages returns the selected images by the user.
     * @return the selected images
     */
    std::map<QString, QImage> getSelectedImages();

    /**
     * @brief isAggregated checks if the user selected to aggregate the results or not
     * @return true if the results shall be aggregated, false if not
     */
    bool isAggregated();

    /**
     * @brief getClassificationQPushButton returns the classificationQPushButton
     *
     * MainWindowHandler uses this method to get the QPushButton and connect its slot to it.
     *
     * @return the classificationQPushButton
     */
    QPushButton* getClassificationQPushButton();

    QComboBox* getOperationModesQComboBox();
    QComboBox* getNeuralNetsQComboBox();
    QVBoxLayout* getPlatformsQVBoxLayout();


        public slots:

    /**
     * @brief processInputImageButton opens a QFileDialog, where the user can select images for the classification
     *
     * processInputImageButton() is connected to the selectInputImagesQPushButton.
     */
    void processInputImageButton();

    /**
     * @brief processConfirmDeletionButton deletes all loaded input images which have a checked QCheckBox.
     *
     * processConfirmDeletionButton() is connected to the confirmDeletionQPushButton.
     */
    void processConfirmDeletionButton();

    /**
     * @brief processAbortDeletionQPushButton unchecks every QCheckBox from the user images.begin()
     *
     * processAbortDeletionQPushButton() is connected to the abortDeletionQPushButton.
     */
    void processAbortDeletionQPushButton();

private:

    Ui::StartWidget *ui;
    QList<QHBoxLayout*> inputImagesLayouts; /*!< Layout order: QCheckBox, QPixmap (the image), QLabel (the file path) */
    QMap<QImage*, QHBoxLayout*> images; /*!< Maps all loaded images to its layout */
    std::map<QString, NetInfo> neuralNetMap; /*!< used to return the selected neural net by using the displayed QString*/
    std::map<QString, PlatformInfo> platformMap; /*!< used to return the selected platform by using the displayed QString */

    void addNeuralNets(std::list<NetInfo> &neuralNets);

    void addPlatforms(std::list<PlatformInfo> &platforms);

    void addOperationModes(std::list<OperationMode> &operationModes);

    QHBoxLayout* addInputImage(QImage* image, const QString &filePath);

    void clearLayout(QLayout *layout);
};
