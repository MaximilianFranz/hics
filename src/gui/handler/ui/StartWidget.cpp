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

    int count = ui->platformsQVBoxLayout->count();

    for(int i = 0; i<count; i++){
        delete ui->platformsQVBoxLayout->itemAt(i);
    }
}

void StartWidget::addNeuralNets(std::list<NetInfo> &neuralNets){
    std::list<NetInfo>::iterator it;

    for(it = neuralNets.begin(); it != neuralNets.end(); ++it){
        QString name = QString::fromStdString(it->getName());
        ui->neuralNetsQComboBox->addItem(name);
    }
}

void StartWidget::addPlatforms(std::list<PlatformInfo> &platforms){
    std::list<PlatformInfo>::iterator it;

    for(it = platforms.begin(); it != platforms.end(); ++it){
        //TODO add platform name when PlatformInfo is implemented.
        QCheckBox* checkbox = new QCheckBox("Platform", this);
        ui->platformsQVBoxLayout->addWidget(checkbox);
    }

}
