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

#include <QFileDialog>
#include <QPixmap>
#include <QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtCore/QMap>
#include <QtWidgets/QErrorMessage>
#include <QtCore/QTimeLine>
#include "handler/ui/StartWidget.h"
#include "ui_StartWidget.h"

StartWidget::StartWidget(std::vector<NetInfo *> &neuralNets, std::vector<PlatformInfo *> &platforms,
                         std::vector<OperationMode> &operationModes, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartWidget) {
    ui->setupUi(this);
    ui->userImagesQWidgetContainer->setLayout(ui->inputImagesQVBoxLayout); //Make input images scrollable

    addNeuralNets(neuralNets);
    addPlatforms(platforms);
    addOperationModes(operationModes);

    //Activates actions when buttons are clicked
    connect(ui->selectInputImagesQPushButton, SIGNAL(clicked()), this, SLOT(processInputImageButton()));
    connect(ui->confirmDeletionQPushButton, SIGNAL(clicked()), this, SLOT(processConfirmDeletionButton()));
    connect(ui->abortDeletionQPushButton, SIGNAL(clicked()), this, SLOT(processAbortDeletionQPushButton()));

    progressBar = new QProgressBar(this);
    progressBar->hide();

    auto layout = new QHBoxLayout();
    layout->addWidget(progressBar);

    ui->buttonsLayout->addLayout(layout);
}

StartWidget::~StartWidget() {
    delete ui;

    //Delete all allocated QImages
    QMapIterator<QPair<QImage *, QString>, QHBoxLayout *> it(images);
    while (it.hasNext()) {
        it.next();
        clearLayout(it.value());
        delete it.value();
        delete it.key().first;
    }
}

void StartWidget::updatePlatforms(std::vector<PlatformInfo *> platforms) {
    std::map<QString, PlatformInfo *>::iterator it;

    //Remove everything from the platformsMap to ensure that the map is empty
    for(it = platformMap.begin(); it != platformMap.end(); ++it){
        platformMap.erase(it);
    }

    //Delete the allocated QCheckBoxes and simultaneously remove them from being displayed
    clearLayout(ui->platformsQVBoxLayout);

    //Add the new platforms to the layout/and map
    addPlatforms(platforms);
}

QHBoxLayout *StartWidget::addInputImage(QImage *image, const QString &filePath) {
    auto layout = new QHBoxLayout();
    auto label = new QLabel(this);

    auto checkBox = new QCheckBox(this);
    connect(checkBox, &QCheckBox::clicked, this, &StartWidget::checkImageSelection);
    layout->addWidget(checkBox, 0);

    //Paint the QImage into a QLabel so that it can be displayed
    auto imageLabel = new QLabel(this);
    imageLabel->setPixmap(QPixmap::fromImage(*image).scaled(227, 227, Qt::KeepAspectRatio));
    layout->addWidget(imageLabel, 1);

    //label->setAlignment(Qt::AlignLeft);
    int pathSize = ((label->size().width() - OFFSET_FILEPATH_DISPLAY) > 0)
                   ? (label->size().width() - OFFSET_FILEPATH_DISPLAY)
                   : label->size().width();
    QFontMetrics fontMetrics = QFontMetrics(QFont());
    label->setText(fontMetrics.elidedText(filePath, Qt::TextElideMode::ElideLeft, pathSize));
    label->setAlignment(Qt::AlignmentFlag::AlignCenter);
    label->setToolTip(filePath);
    label->setToolTipDuration(-1);

    layout->addWidget(label, 1);

    ui->inputImagesQVBoxLayout->addLayout(layout);

    return layout;
}

void StartWidget::processInputImageButton() {
    QStringList fileNames = QFileDialog::getOpenFileNames(
        this,
        "Select one or more files to open",
        directoryPath,
        "Images (*.png *.jpg *.jpeg *.PNG *.JPG *.JPEG)");

    fileNames = removeDuplicateSelectedImages(fileNames);
    //Create a QImage to every selected file path
    for (int i = 0; i < fileNames.size(); ++i) {
        auto image = new QImage();
        //if(images.fileNames.at(i))
        if (image->load(fileNames.at(i))) {
            //Display the image together with a check box and its file path
            QHBoxLayout *layout = addInputImage(image, fileNames.at(i));
            images.insert(QPair<QImage *, QString>(image, fileNames.at(i)), layout);
            directoryPath = QFileInfo(fileNames.at(i)).path();
        } else {
            delete image;
        }
    }

    //Refresh select all button to match the current state of the images (all checked/all unchecked etc.)
    checkImageSelection();
}

QStringList StartWidget::removeDuplicateSelectedImages(const QStringList &filePaths) {
    QStringList output = filePaths;
    QMapIterator<QPair<QImage *, QString>, QHBoxLayout *> it(images);
    std::vector<QString> duplicateFilePaths;

    //Check if a selected image has already been loaded into the application
    while (it.hasNext()) {
        it.next();

        for (int i = 0; i < filePaths.size(); ++i) {
            if (it.key().second == filePaths.at(i)) {
                duplicateFilePaths.push_back(filePaths.at(i));
            }
        }
    }

    for (unsigned int i = 0; i < duplicateFilePaths.size(); ++i) {
        output.removeAt(output.indexOf(duplicateFilePaths.at(i)));
    }

    return output;
}

void StartWidget::processConfirmDeletionButton() {
    QMapIterator<QPair<QImage *, QString>, QHBoxLayout *> it(images);

    //Get every QImage's check box inside the layout and delete the image and layout if it is checked
    while (it.hasNext()) {
        it.next();
        QCheckBox *checkBox;
        if(it.value()->itemAt(0)->widget()) {
            if ((checkBox = (QCheckBox *) (it.value()->itemAt(0)->widget()))) {
                if (checkBox->isChecked()) {
                    clearLayout(it.value());
                    delete it.value();
                    delete it.key().first;
                    images.remove(it.key());
                }
            }
        }
    }

    if (areAllSelected() && (!images.empty())) {
        ui->abortDeletionQPushButton->setText("Deselect all");
    } else  {
        ui->abortDeletionQPushButton->setText("Select all");
    }

    renumerateImages();
}

void StartWidget::renumerateImages() {
    for (int i = 0; i < ui->inputImagesQVBoxLayout->count(); ++i) {
        ((QCheckBox *) (ui->inputImagesQVBoxLayout->itemAt(i)->layout()->itemAt(0)->widget()))->setText(
            QString::number(i + 1));
    }
}

bool StartWidget::areAllSelected() {
    //Returns true if all image checkboxes are unselected, false if at least one is checked
    bool result = true;
    QMapIterator<QPair<QImage *, QString>, QHBoxLayout *> it(images);
    while (it.hasNext()) {
        it.next();
        QCheckBox *checkBox;
        if ((checkBox = (QCheckBox *) (it.value()->itemAt(0)->widget()))) {
            if (!checkBox->isChecked()) {
                result = false;
                break;
            }
        }
    }
    return result;
}

void StartWidget::checkImageSelection() {
    //Check the current state of the checkboxes. Always say "Select all" unless all boxes are checked
    if (areAllSelected()) {
        ui->abortDeletionQPushButton->setText("Deselect all");
    } else {
        ui->abortDeletionQPushButton->setText("Select all");
    }
}

void StartWidget::processAbortDeletionQPushButton() {
    QMapIterator<QPair<QImage *, QString>, QHBoxLayout *> it(images);

    //If all are selected we want to deselect all, else we want to select all
    if (areAllSelected()) {
        while (it.hasNext()) {
            it.next();
            QCheckBox *checkBox;
            if ((checkBox = (QCheckBox *) (it.value()->itemAt(0)->widget()))) {
                if (checkBox->isChecked()) {
                    checkBox->setChecked(false);
                }
            }
        }
        if (!images.empty()) ui->abortDeletionQPushButton->setText("Select all");
    } else {
        while (it.hasNext()) {
            it.next();
            QCheckBox *checkBox;
            if ((checkBox = (QCheckBox *) (it.value()->itemAt(0)->widget()))) {
                if (!checkBox->isChecked()) {
                    checkBox->setChecked(true);
                }
            }
        }
        if (!images.empty()) ui->abortDeletionQPushButton->setText("Deselect all");
    }
}

void StartWidget::addNeuralNets(std::vector<NetInfo *> &neuralNets) {
    std::vector<NetInfo *>::iterator it;

    for (it = neuralNets.begin(); it != neuralNets.end(); ++it) {
        QString name = QString::fromStdString((*it)->getName());
        neuralNetMap.insert(std::pair<QString, NetInfo *>(name, *it));
        ui->neuralNetsQComboBox->addItem(name);
    }
}

void StartWidget::addPlatforms(std::vector<PlatformInfo *> &platforms) {
    std::vector<PlatformInfo *>::iterator it;

    for (it = platforms.begin(); it != platforms.end(); ++it) {
        QString name = QString::fromStdString((*it)->getDescription());

        platformMap.insert(std::pair<QString, PlatformInfo *>(name, *it));
        auto checkbox = new QCheckBox(name, this);
        ui->platformsQVBoxLayout->addWidget(checkbox);
    }
}

void StartWidget::addOperationModes(std::vector<OperationMode> &operationModes) {
    std::vector<OperationMode>::iterator it;

    for (it = operationModes.begin(); it != operationModes.end(); ++it) {
        ui->operationModesQComboBox->addItem(QString::fromStdString(OperationModeString::getName(*it)));
    }
}

void StartWidget::clearLayout(QLayout *layout) {
    QLayoutItem *item;

    //Removes every item inside the layout and delete it
    while ((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
            delete item->widget();
        }
    }
}

QErrorMessage* StartWidget::displayErrorMessage(const QString message) {
    auto error = new QErrorMessage(this);
    error->setWindowTitle("Error");
    error->showMessage(message);
    return error;
}

NetInfo StartWidget::getSelectedNeuralNet() {
    QString name = ui->neuralNetsQComboBox->currentText();
    auto it = neuralNetMap.find(name);

    if (it == neuralNetMap.end()) {
        displayErrorMessage(QString("Please select a neural net for the classification."));
    }

    return *it->second;
}

void StartWidget::displayProgress() {
    ui->classificationQPushButton->hide();
    ui->selectInputImagesQPushButton->hide();

    progressBar->setRange(0, 0);
    progressBar->show();

    disableWidgets(true);
}

void StartWidget::resetProgressDisplay() {
    progressBar->setMaximum(100);
    progressBar->setValue(100);
    progressBar->hide();

    ui->classificationQPushButton->show();
    ui->selectInputImagesQPushButton->show();

    disableWidgets(false);
}

void StartWidget::disableWidgets(bool disable) {
    ui->selectInputImagesQPushButton->setDisabled(disable);
    ui->classificationQPushButton->setDisabled(disable);
    ui->operationModesQComboBox->setDisabled(disable);
    ui->neuralNetsQComboBox->setDisabled(disable);
    ui->aggregateResultsQCheckBox->setDisabled(disable);
    ui->abortDeletionQPushButton->setDisabled(disable);
    ui->confirmDeletionQPushButton->setDisabled(disable);

    for (int i = 0; i < ui->platformsQVBoxLayout->count(); ++i) {
        QLayoutItem *item = ui->platformsQVBoxLayout->itemAt(i);
        if (item->widget()) {
            item->widget()->setDisabled(disable);
        }
    }

    QMapIterator<QPair<QImage *, QString>, QHBoxLayout *> it(images);
    //Get every QImage's check box inside the layout and set the disabled state
    while (it.hasNext()) {
        it.next();
        if (it.value()->itemAt(0)->widget()) {
            it.value()->itemAt(0)->widget()->setDisabled(disable);
        }
    }
}

std::vector<PlatformInfo> StartWidget::getSelectedPlatforms() {
    std::vector<PlatformInfo> selectedPlatforms;
    QVBoxLayout *layout = ui->platformsQVBoxLayout;

    //Add only the selected platforms to the output vector
    if (layout) {
        for (int i = 0; i < layout->count(); ++i) {
            QCheckBox *checkBox;
            if (layout->itemAt(i)->widget()) {
                checkBox = (QCheckBox *) (layout->itemAt(i)->widget());
                if (checkBox->isChecked()) {
                    try {
                        PlatformInfo *platform = platformMap.at(checkBox->text());
                        selectedPlatforms.push_back(*platform);
                    } catch (std::out_of_range &e) {
                        e.what();
                    }
                }
            }
        }
    }

    if (selectedPlatforms.empty()) {
        displayErrorMessage(QString("Please select at least one platform."));
        return selectedPlatforms;
    } else {
        return selectedPlatforms;
    }
}

OperationMode StartWidget::getSelectedOperationMode() {
    return OperationModeString::getMode(ui->operationModesQComboBox->currentText().toStdString());
}

bool StartWidget::isAggregated() {
    return ui->aggregateResultsQCheckBox->isChecked();
}

void StartWidget::resizeEvent(QResizeEvent *event) {
    widgetResized();
    QWidget::resizeEvent(event);
}

void StartWidget::widgetResized() {
    QMapIterator<QPair<QImage *, QString>, QHBoxLayout *> it(images);

    while (it.hasNext()) {
        it.next();
        auto filePathLabel = (QLabel *) (it.value()->itemAt(2)->widget());
        int newSize = ((filePathLabel->size().width() - OFFSET_FILEPATH_DISPLAY) > 0)
                      ? (filePathLabel->size().width() - OFFSET_FILEPATH_DISPLAY)
                      : filePathLabel->size().width();
        QFontMetrics fontMetrics = QFontMetrics(QFont());
        filePathLabel->setText(fontMetrics.elidedText(it.key().second, Qt::TextElideMode::ElideLeft, newSize));
    }
}

std::map<QString, QImage> StartWidget::getSelectedImages() {
    std::map<QString, QImage> output;

    QMapIterator<QPair<QImage *, QString>, QHBoxLayout *> it(images);

    while (it.hasNext()) {
        it.next();
        output.insert(std::pair<QString, QImage>(it.key().second, *(it.key().first)));
    }

    if (output.empty()) {
        displayErrorMessage(QString("Please select at least one image for the classification."));
    }

    return output;
}


QPushButton *StartWidget::getClassificationQPushButton() {
    return ui->classificationQPushButton;
}

QComboBox *StartWidget::getOperationModesQComboBox() {
    return ui->operationModesQComboBox;
}

QComboBox *StartWidget::getNeuralNetsQComboBox() {
    return ui->neuralNetsQComboBox;
}

QVBoxLayout *StartWidget::getPlatformsQVBoxLayout() {
    return ui->platformsQVBoxLayout;
}

QCheckBox *StartWidget::getAggregateResultsQCheckBox() {
    return ui->aggregateResultsQCheckBox;
}

QMap<QPair<QImage *, QString>, QHBoxLayout *> *StartWidget::getImagesMap() {
    return &images;
}