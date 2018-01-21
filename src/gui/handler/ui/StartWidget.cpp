#include "handler/ui/StartWidget.h"
#include "ui_StartWidget.h"

StartWidget::StartWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartWidget)
{
    ui->setupUi(this);
    ui->userImagesQWidgetContainer->setLayout(ui->inputImagesQVBoxLayout);
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
    imageLabel->setPixmap(QPixmap::fromImage(*image));

    layout->addWidget(imageLabel, 1);

    ui->inputImagesQVBoxLayout->addLayout(layout);

    return layout;
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
