/* Copyright 2018 The HICS Authors
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall
 * be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 */

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
#include <QtWidgets/QCheckBox>
#include <QtCore/QDir>
#include <QTimer>

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
class StartWidget : public QWidget {

Q_OBJECT

private:

    Ui::StartWidget *ui;
    QList<QHBoxLayout *> inputImagesLayouts; /*!< Layout order: QCheckBox, QPixmap (the image), QLabel (the file path) */
    QMap<QPair<QImage *, QString>, QHBoxLayout *> images; /*!< Maps all loaded images to its layout */
    std::map<QString, NetInfo *> neuralNetMap; /*!< used to return the selected neural net by using the displayed QString*/
    std::map<QString, PlatformInfo *> platformMap; /*!< used to return the selected platform by using the displayed QString */

    QString directoryPath = QDir::homePath(); /*!< The last opened directory path of the QFileDialog */

    const int OFFSET_FILEPATH_DISPLAY = 20;

    void addNeuralNets(std::vector<NetInfo *> &neuralNets);

    void addPlatforms(std::vector<PlatformInfo *> &platforms);

    void addOperationModes(std::vector<OperationMode> &operationModes);

    QStringList removeDuplicateSelectedImages(const QStringList &filePaths);

    QHBoxLayout *addInputImage(QImage *image, const QString &filePath);

    void clearLayout(QLayout *layout);

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
    explicit StartWidget(std::vector<NetInfo *> &neuralNets, std::vector<PlatformInfo *> &platforms,
                         std::vector<OperationMode> &operationModes, QWidget *parent = 0);

    /**
     * The destructor to delete all allocated memory on the heap.
     */
    ~StartWidget();

    void displayErrorMessage(const QString message);

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
     * @brief getSelectedOperationMode returns the selected operation mode.
     * @return the selected operation mode
     */
    OperationMode getSelectedOperationMode();

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
    QPushButton *getClassificationQPushButton();

    /**
     * @brief getOperationModesQComboBox returns the QComboBox containing the operation modes
     * @return the combo box containing the operation modes
     */
    QComboBox *getOperationModesQComboBox();

    /**
     * @brief getNeuralNetsQComboBox returns the QComboBox containing the available neural nets
     * @return the combo box containing the available neural nets
     */
    QComboBox *getNeuralNetsQComboBox();

    /**
     * @brief getPlatformsQVBoxLayout return a vertical layout containing the available platforms for the classification
     * @return the layout containing all available platforms as checkboxes
     */
    QVBoxLayout *getPlatformsQVBoxLayout();

    /**
     * @brief getAggregateResultsQCheckBox returns the QCheckBox which indicates if the results shall be aggregated or not.
     * @return the check box where the user can select to aggregate the results or not
     */
    QCheckBox *getAggregateResultsQCheckBox();

    /**
     * @brief getImagesMap returns the images map which hold all selected input images together with its layouts
     * @return the image map
     */
    QMap<QPair<QImage *, QString>, QHBoxLayout *> *getImagesMap();

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

protected:

    void resizeEvent(QResizeEvent * event);

private slots:

    void widgetResized();

};
