#include <QString>
#include <QCheckBox>
#include "handler/ui/StartWidget.h"
#include "ui_StartWidget.h"

StartWidget::StartWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartWidget)
{
    ui->setupUi(this);
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

QPushButton* StartWidget::getSelectInputImagesQPushButton(){
    return ui->selectInputImagesQPushButton;
}
