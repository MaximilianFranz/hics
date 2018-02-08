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
#include "handler/ui/StartWidget.h"
#include "ui_StartWidget.h"

StartWidget::StartWidget(std::vector<NetInfo*> &neuralNets, std::vector<PlatformInfo*> &platforms,
                         std::vector<OperationMode> &operationModes, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartWidget)
{
    ui->setupUi(this);
    ui->userImagesQWidgetContainer->setLayout(ui->inputImagesQVBoxLayout); //Make input images scrollable

    addNeuralNets(neuralNets);
    addPlatforms(platforms);
    addOperationModes(operationModes);

    //Activates actions when buttons are clicked
    connect(ui->selectInputImagesQPushButton, SIGNAL(clicked()), this, SLOT(processInputImageButton()));
    connect(ui->confirmDeletionQPushButton, SIGNAL(clicked()), this, SLOT(processConfirmDeletionButton()));
    connect(ui->abortDeletionQPushButton, SIGNAL(clicked()), this, SLOT(processAbortDeletionQPushButton()));

    resizeTimer.setSingleShot(true);
    connect(&resizeTimer, SIGNAL(timeout()), SLOT(widgetResized()));
}

StartWidget::~StartWidget()
{
    delete ui;

    //Delete all allocated QImages
    QMapIterator<QPair<QImage*, QString>, QHBoxLayout*> it(images);
    while (it.hasNext()) {
        it.next();
        clearLayout(it.value());
        delete it.key().first;
    }
}

QHBoxLayout* StartWidget::addInputImage(QImage* image, const QString &filePath){
    QHBoxLayout* layout = new QHBoxLayout();
    QCheckBox* checkBox = new QCheckBox(this);
    QLabel* label = new QLabel(this);

    layout->addWidget(checkBox, 0);

    //Paint the QImage into a QLabel so that it can be displayed
    QLabel* imageLabel = new QLabel(this);
    imageLabel->setPixmap(QPixmap::fromImage(*image).scaled(227, 227, Qt::KeepAspectRatio));
    layout->addWidget(imageLabel, 1);

    //label->setAlignment(Qt::AlignLeft);
    int pathSize = ((label->size().width() - OFFSET_FILEPATH_DISPLAY) > 0)
                   ? (label->size().width() - OFFSET_FILEPATH_DISPLAY)
                   : label->size().width();
    QFontMetrics fontMetrics = QFontMetrics(QFont());
    label->setText(fontMetrics.elidedText(filePath,Qt::TextElideMode::ElideLeft, pathSize));
    label->setAlignment(Qt::AlignmentFlag::AlignCenter);
    label->setToolTip(filePath);
    label->setToolTipDuration(-1);

    layout->addWidget(label, 1);

    ui->inputImagesQVBoxLayout->addLayout(layout);

    return layout;
}

void StartWidget::processInputImageButton(){
    QStringList fileNames = QFileDialog::getOpenFileNames(
                            this,
                            "Select one or more files to open",
                            directoryPath,
                            "Images (*.png *.jpg *.jpeg *.PNG *.JPG *.JPEG)");

    fileNames = removeDuplicateSelectedImages(fileNames);
    //Create a QImage to every selected file path
    for(int i = 0; i<fileNames.size(); ++i){
        QImage* image = new QImage();
        //if(images.fileNames.at(i))
        if(image->load(fileNames.at(i))){
            //Display the image together with a check box and its file path
            QHBoxLayout* layout = addInputImage(image, fileNames.at(i));
            images.insert(QPair<QImage*, QString>(image, fileNames.at(i)), layout);
            directoryPath = QFileInfo(fileNames.at(i)).path();
        } else {
            delete image;
        }
    }
}

QStringList StartWidget::removeDuplicateSelectedImages(const QStringList &filePaths){
    QStringList output = filePaths;
    QMapIterator<QPair<QImage*, QString>, QHBoxLayout*>it(images);
    std::vector<QString> duplicateFilePaths;

    //Check if a selected image has already been loaded into the application
    while(it.hasNext()){
        it.next();

        for(int i = 0; i<filePaths.size(); ++i){
            if(it.key().second == filePaths.at(i)){
                duplicateFilePaths.push_back(filePaths.at(i));
            }
        }
    }

    for(int i = 0; i<duplicateFilePaths.size(); ++i){
        output.removeAt(output.indexOf(duplicateFilePaths.at(i)));
    }

    return output;
}

void StartWidget::processConfirmDeletionButton(){
    QMapIterator<QPair<QImage*, QString>, QHBoxLayout*> it(images);

    //Get every QImage's check box inside the layout and delete the image and layout if it is checked
    while (it.hasNext()) {
        it.next();
        QCheckBox* checkBox;
        //TODO maybe check for it.value()->itemAt(0) if this is a valid pointer
        if((checkBox = (QCheckBox*)(it.value()->itemAt(0)->widget()))){
            if(checkBox->isChecked()){
                clearLayout(it.value());
                delete it.value();
                delete it.key().first;
                images.remove(it.key());
            }
        }
    }
}

void StartWidget::processAbortDeletionQPushButton(){
    QMapIterator<QPair<QImage*, QString>, QHBoxLayout*> it(images);

    //Uncheck every image check box
    while(it.hasNext()){
        it.next();
        QCheckBox* checkBox;
        if((checkBox = (QCheckBox*)(it.value()->itemAt(0)->widget()))){
            checkBox->setChecked(false);
        }
    }
}


void StartWidget::addNeuralNets(std::vector<NetInfo*> &neuralNets){
    std::vector<NetInfo*>::iterator it;

    for(it = neuralNets.begin(); it != neuralNets.end(); ++it){
        QString name = QString::fromStdString((*it)->getName());
        neuralNetMap.insert(std::pair<QString, NetInfo*>(name, *it));
        ui->neuralNetsQComboBox->addItem(name);
    }
}

void StartWidget::addPlatforms(std::vector<PlatformInfo*> &platforms){
    std::vector<PlatformInfo*>::iterator it;

    for(it = platforms.begin(); it != platforms.end(); ++it){
        QString name = QString::fromStdString((*it)->getDescription());

        platformMap.insert(std::pair<QString, PlatformInfo*>(name, *it));
        QCheckBox* checkbox = new QCheckBox(name, this);
        ui->platformsQVBoxLayout->addWidget(checkbox);
    }
}

void StartWidget::addOperationModes(std::vector<OperationMode> &operationModes){
    std::vector<OperationMode>::iterator it;

    for(it = operationModes.begin(); it != operationModes.end(); ++it){
        ui->operationModesQComboBox->addItem(QString::fromStdString(OperationModeString::getName(*it)));
    }
}

void StartWidget::clearLayout(QLayout *layout){
    QLayoutItem* item;

    //Removes every item inside the layout and delete it
    while((item = layout->takeAt(0))){
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if(item->widget()){
            delete item->widget();
        }
    }
}

void StartWidget::displayErrorMessage(const QString message){
    QErrorMessage* error = new QErrorMessage(this);
    error->setWindowTitle("Error");
    error->showMessage(message);
}

NetInfo StartWidget::getSelectedNeuralNet(){
    QString name = ui->neuralNetsQComboBox->currentText();
    std::map<QString, NetInfo*>::iterator it = neuralNetMap.find(name);

    if(it == neuralNetMap.end()){
        //TODO throw exception here
        displayErrorMessage(QString("Please select a neural net for the classification."));
    }

    return *it->second;
}

std::vector<PlatformInfo> StartWidget::getSelectedPlatforms(){
    std::vector<PlatformInfo> selectedPlatforms;
    QVBoxLayout* layout = ui->platformsQVBoxLayout;

    //Add only the selected platforms to the output vector
    if(layout){
        for(int i = 0; i<layout->count(); ++i){
            QCheckBox* checkBox;
            if(layout->itemAt(i)->widget()){
                checkBox = (QCheckBox*)(layout->itemAt(i)->widget());
                if(checkBox->isChecked()){
                    try{
                        PlatformInfo* platform = platformMap.at(checkBox->text());
                        selectedPlatforms.push_back(*platform);
                    } catch (std::out_of_range e) {
                        e.what();
                    }
                }
            }
        }
    }

    if(selectedPlatforms.empty()){
        displayErrorMessage(QString("Please select at least one platform."));
        return selectedPlatforms;
    } else {
        return selectedPlatforms;
    }
}

OperationMode StartWidget::getSelectedOperationMode(){
    return OperationModeString::getMode(ui->operationModesQComboBox->currentText().toStdString());
}

bool StartWidget::isAggregated(){
    return ui->aggregateResultsQCheckBox->isChecked();
}

void StartWidget::resizeEvent(QResizeEvent *event) {
    resizeTimer.start(500);
    QWidget::resizeEvent(event);
}

void StartWidget::widgetResized() {
    //TODO resize file labels
    QMapIterator<QPair<QImage*, QString>, QHBoxLayout*>it (images);

    while(it.hasNext()){
        it.next();
        QLabel* filePathLabel = (QLabel*)(it.value()->itemAt(2)->widget());
        int newSize = ((filePathLabel->size().width() - OFFSET_FILEPATH_DISPLAY) > 0)
                      ? (filePathLabel->size().width() - OFFSET_FILEPATH_DISPLAY)
                      : filePathLabel->size().width();
        QFontMetrics fontMetrics = QFontMetrics(QFont());
        filePathLabel->setText(fontMetrics.elidedText(it.key().second, Qt::TextElideMode::ElideLeft, newSize));
    }
}

std::map<QString, QImage> StartWidget::getSelectedImages(){
    std::map<QString, QImage> output;

    QMapIterator<QPair<QImage*, QString>, QHBoxLayout*> it(images);

    while(it.hasNext()){
        it.next();
        output.insert(std::pair<QString, QImage>(it.key().second, *(it.key().first)));
    }

    if(output.empty()){
        displayErrorMessage(QString("Please select at least one image for the classification."));
    }

    return output;
}


QPushButton* StartWidget::getClassificationQPushButton(){
    return ui->classificationQPushButton;
}

QComboBox* StartWidget::getOperationModesQComboBox(){
    return ui->operationModesQComboBox;
}

QComboBox* StartWidget::getNeuralNetsQComboBox(){
    return ui->neuralNetsQComboBox;
}

QVBoxLayout* StartWidget::getPlatformsQVBoxLayout(){
    return ui->platformsQVBoxLayout;
}

QCheckBox* StartWidget::getAggregateResultsQCheckBox(){
    return ui->aggregateResultsQCheckBox;
}

QMap<QPair<QImage*, QString>, QHBoxLayout*>* StartWidget::getImagesMap(){
    return &images;
};

