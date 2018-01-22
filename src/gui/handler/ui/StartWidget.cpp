#include "handler/ui/StartWidget.h"
#include "ui_StartWidget.h"

StartWidget::StartWidget(std::list<NetInfo> &neuralNets, std::list<PlatformInfo> &platforms,
                         std::list<OperationMode> &operationModes, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartWidget)
{
    ui->setupUi(this);
    ui->userImagesQWidgetContainer->setLayout(ui->inputImagesQVBoxLayout);
    addNeuralNets(neuralNets);
    addPlatforms(platforms);
    addOperationModes(operationModes);

    connect(ui->selectInputImagesQPushButton, SIGNAL(clicked()), this, SLOT(processInputImageButton()));
    connect(ui->confirmDeletionQPushButton, SIGNAL(clicked()), this, SLOT(processConfirmDeletionButton()));
    connect(ui->abortDeletionQPushButton, SIGNAL(clicked()), this, SLOT(processAbortDeletionQPushButton()));
}

StartWidget::~StartWidget()
{
    delete ui;

    //TODO change this if there are more pointers to delete.
    int count = ui->platformsQVBoxLayout->count();
    for(int i = 0; i<count; i++){
        delete ui->platformsQVBoxLayout->itemAt(i);
    }
}

void StartWidget::addNeuralNet(const QString &neuralNet){

    ui->neuralNetsQComboBox->addItem(neuralNet);
}

void StartWidget::addPlatform(const QString &platform){

    QCheckBox* checkbox = new QCheckBox(platform, this);
    ui->platformsQVBoxLayout->addWidget(checkbox);
}

void StartWidget::addOperationMode(const QString &operationMode){
    ui->operationModesQComboBox->addItem(operationMode);
}

QHBoxLayout* StartWidget::addInputImage(QImage* image){
    QHBoxLayout* layout = new QHBoxLayout();
    QCheckBox* checkBox = new QCheckBox();

    layout->addWidget(checkBox, 0);
    QLabel* imageLabel = new QLabel();
    imageLabel->setPixmap(QPixmap::fromImage(*image).scaled(227, 227, Qt::KeepAspectRatio));

    layout->addWidget(imageLabel, 1);

    ui->inputImagesQVBoxLayout->addLayout(layout);

    return layout;
}

void StartWidget::processInputImageButton(){
    QStringList fileNames = QFileDialog::getOpenFileNames(
                            this,
                            "Select one or more files to open",
                            "/home",
                            "Images (*.png *.xpm *.jpg)");

    for(int i = 0; i<fileNames.size(); ++i){
        QImage* image = new QImage();
        if(image->load(fileNames.at(i))){
            //TODO delete allocated images in destructor
            QHBoxLayout* layout = addInputImage(image);
            images.insert(image, layout);
        } else {
            delete image;
        }
    }
}

void StartWidget::processConfirmDeletionButton(){

    QMapIterator<QImage*, QHBoxLayout*> it(images);
    while (it.hasNext()) {
        it.next();
        QCheckBox* checkBox;
        //TODO maybe check for it.value()->itemAt(0) if this is a valid pointer
        if(checkBox = (QCheckBox*)(it.value()->itemAt(0)->widget())){
                if(checkBox->isChecked()){
                    clearLayout(it.value());
                    QHBoxLayout* tempLayout = it.value();
                    QImage* tempImage = it.key();
                    images.remove(it.key());
                    delete tempLayout;
                    delete tempImage;
                }
        }
    }
}

void StartWidget::processAbortDeletionQPushButton(){
    QMapIterator<QImage*, QHBoxLayout*> it(images);
    while(it.hasNext()){
        it.next();
        QCheckBox* checkBox;
        if(checkBox = (QCheckBox*)(it.value()->itemAt(0)->widget())){
            checkBox->setChecked(false);
        }
    }
}


void StartWidget::addNeuralNets(std::list<NetInfo> &neuralNets){
    std::list<NetInfo>::iterator it;

    for(it = neuralNets.begin(); it != neuralNets.end(); ++it){
        QString name = QString::fromStdString(it->getName());

        neuralNetMap.insert(std::pair<QString, NetInfo>(name, *it));
        addNeuralNet(name);
    }
}

void StartWidget::addPlatforms(std::list<PlatformInfo> &platforms){
    std::list<PlatformInfo>::iterator it;

    for(it = platforms.begin(); it != platforms.end(); ++it){
        QString name = QString::fromStdString(it->getDescription());

        platformMap.insert(std::pair<QString, PlatformInfo>(name, *it));
        addPlatform(name);
    }
}

void StartWidget::addOperationModes(std::list<OperationMode> &operationModes){
    std::list<OperationMode>::iterator it;

    for(it = operationModes.begin(); it != operationModes.end(); ++it){
        //TODO add operation mode name when its implemented.
        //QString name = QString::fromStdString(it->);
        addOperationMode("Operation mode");
    }
}

void StartWidget::clearLayout(QLayout *layout){
    QLayoutItem* item;
    while(item = layout->takeAt(0)){
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
    try{
        return neuralNetMap.at(name);

    } catch (std::out_of_range e) {
        e.what();
    }
}

std::vector<PlatformInfo> StartWidget::getSelectedPlatforms(){
    std::vector<PlatformInfo> selectedPlatforms;

    QVBoxLayout* layout = ui->platformsQVBoxLayout;
    if(layout){
        for(int i = 0; i<layout->count(); ++i){
            QCheckBox* checkBox;
            if(layout->itemAt(i)->widget()){
                checkBox = (QCheckBox*)(layout->itemAt(i)->widget());
                if(checkBox->isChecked()){
                    try{
                        PlatformInfo platform = platformMap.at(checkBox->text());
                        selectedPlatforms.push_back(platform);
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

QPushButton* StartWidget::getSelectInputImagesQPushButton(){
    return ui->selectInputImagesQPushButton;
}

QPushButton* StartWidget::getConfirmDeletionQPushButton(){
    return ui->confirmDeletionQPushButton;
}

QVBoxLayout* StartWidget::getInputImagesQVBoxLayout(){
    return ui->inputImagesQVBoxLayout;
}
