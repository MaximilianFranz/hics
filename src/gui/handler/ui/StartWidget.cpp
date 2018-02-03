#include <QFileDialog>
#include <QPixmap>
#include <QCheckBox>
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
}

StartWidget::~StartWidget()
{
    delete ui;

    //Delete all allocated QImages
    QMapIterator<QImage*, QHBoxLayout*> it(images);
    while (it.hasNext()) {
        it.next();
        clearLayout(it.value());
        delete it.key();
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

    label->setAlignment(Qt::AlignLeft);
    QFontMetrics fontMetrics = QFontMetrics(QFont());
    label->setText(fontMetrics.elidedText(filePath,Qt::TextElideMode::ElideLeft, 150));
    label->setAlignment(Qt::AlignmentFlag::AlignCenter);
    layout->addWidget(label, 1);

    ui->inputImagesQVBoxLayout->addLayout(layout);

    return layout;
}

void StartWidget::processInputImageButton(){
    QStringList fileNames = QFileDialog::getOpenFileNames(
                            this,
                            "Select one or more files to open",
                            directoryPath,
                            "Images (*.png *.jpg *.jpeg)");

    //Create a QImage to every selected file path
    for(int i = 0; i<fileNames.size(); ++i){
        QImage* image = new QImage();
        if(image->load(fileNames.at(i))){
            //Display the image together with a check box and its file path
            QHBoxLayout* layout = addInputImage(image, fileNames.at(i));
            images.insert(image, layout);
            directoryPath = QFileInfo(fileNames.at(i)).path();
        } else {
            delete image;
        }
    }
}

void StartWidget::processConfirmDeletionButton(){
    QMapIterator<QImage*, QHBoxLayout*> it(images);

    //Get every QImage's check box inside the layout and delete the image and layout if it is checked
    while (it.hasNext()) {
        it.next();
        QCheckBox* checkBox;
        //TODO maybe check for it.value()->itemAt(0) if this is a valid pointer
        if((checkBox = (QCheckBox*)(it.value()->itemAt(0)->widget()))){
            if(checkBox->isChecked()){
                clearLayout(it.value());
                delete it.value();
                delete it.key();
                images.remove(it.key());
            }
        }
    }
}

void StartWidget::processAbortDeletionQPushButton(){
    QMapIterator<QImage*, QHBoxLayout*> it(images);

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

NetInfo StartWidget::getSelectedNeuralNet(){
    QString name = ui->neuralNetsQComboBox->currentText();
    std::map<QString, NetInfo*>::iterator it = neuralNetMap.find(name);

    if(it == neuralNetMap.end()){
        //TODO throw exception here

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
        //TODO Error message -> you must selecte at least one platform
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

std::map<QString, QImage> StartWidget::getSelectedImages(){
    std::map<QString, QImage> output;

    QMapIterator<QImage*, QHBoxLayout*> it(images);
    while(it.hasNext()){
        it.next();

        if(it.value()->itemAt(2)){
            if(it.value()->itemAt(2)->widget()){
                //TODO maybe check for cast to QLabel
                QLabel* label = (QLabel*)(it.value()->itemAt(2)->widget());
                output.insert(std::pair<QString, QImage>(label->text(), *(it.key())));
            }
        }
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

QMap<QImage*, QHBoxLayout*>* StartWidget::getImagesMap(){
    return &images;
};

