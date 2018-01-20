#include "handler/ui/StartWidget.h"
#include "ui_StartWidget.h"

StartWidget::StartWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartWidget)
{
    ui->setupUi(this);
    ui->userImagesQWidgetContainer->setLayout(ui->userImagesQGridLayout);
}

StartWidget::~StartWidget()
{
    delete ui;

    //TODO change this if there are more pointers to delete.
    int count = ui->platformsQVBoxLayout->count();
    for(int i = 0; i<count; i++){
        delete ui->platformsQVBoxLayout->itemAt(i);
    }

    count = ui->userImagesQGridLayout->count();
    for(int i = 0; i<count; i++){
        delete ui->userImagesQGridLayout->itemAt(i);
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

QCheckBox* StartWidget::addInputImage(QImage *image, QCheckBox* checkBoxParam){
    //TODO resize pictures, and add them to scroll area
    QCheckBox* checkBox;
    if(!checkBoxParam){
        checkBox = new QCheckBox("", this);
    } else {
        checkBox = checkBoxParam;
    }
    QLabel* imageLabel = new QLabel();
    imageLabel->setPixmap(QPixmap::fromImage(*image));

    int row = ui->userImagesQGridLayout->rowCount();
    ui->userImagesQGridLayout->addWidget(checkBox, row, 0);
    ui->userImagesQGridLayout->addWidget(imageLabel, row, 1);

    return checkBox;
}

QPushButton* StartWidget::getSelectInputImagesQPushButton(){
    return ui->selectInputImagesQPushButton;
}

QPushButton* StartWidget::getConfirmDeletionQPushButton(){
    return ui->confirmDeletionQPushButton;
}

QGridLayout* StartWidget::getUserImagesQGridLayout(){
    return ui->userImagesQGridLayout;
}
