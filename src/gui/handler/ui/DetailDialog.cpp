#include "DetailDialog.h"
#include "ui_DetailDialog.h"

DetailDialog::DetailDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DetailDialog)
{
    ui->setupUi(this);
}

void DetailDialog::insertDetails(const ClassificationResult* result){
    PerformanceData performance = result->getPerformance();

    ui->computationTimeQLabel->setText(QString::number(performance.getComputationTime()));
    ui->powerConsumptionQLabel->setText(QString::number(performance.getPowerConsumption()));
    std::vector<std::pair<PlatformInfo, float>> platformUsage = performance.getPlatformUsage();

    QString platformText = "";
    for(int i = 0; i<platformUsage.size(); ++i){
        std::pair<PlatformInfo, float> pair = platformUsage[i];
        platformText += QString::fromStdString(pair.first.getDescription()) + ": " + QString::number(pair.second) + "%, ";
    }

    if(platformText.size() > 0){
        platformText.remove((platformText.size()-2), 2);
    }

    ui->platformUsageQLabel->setText(platformText);

    //TODO add attached Platforms
}


DetailDialog::~DetailDialog()
{
    delete ui;
}
