#include "DetailDialog.h"
#include "ui_DetailDialog.h"

DetailDialog::DetailDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DetailDialog)
{
    ui->setupUi(this);
}

void DetailDialog::insertDetails(const ClassificationResult* result){
    //Display the computation time.
    ui->computationTimeQLabel->setText(QString::number(result->getPerformance().getComputationTime()));

    //Display the power consumption
    ui->powerConsumptionQLabel->setText(QString::number(result->getPerformance().getPowerConsumption()));
    std::vector<std::pair<PlatformInfo, float>> platformUsage = result->getPerformance().getPlatformUsage();

    //Add the used platforms and their usage to a QString
    QString platformText = "";
    for(int i = 0; i<platformUsage.size(); ++i){
        std::pair<PlatformInfo, float> pair = platformUsage[i];
        platformText += QString::fromStdString(pair.first.getDescription()) + ": " + QString::number(pair.second) + "%, ";
    }

    //Remove the last white space and comma from the QString
    if(platformText.size() > 0){
        platformText.remove((platformText.size()-2), 2);
    }

    //Display the platforms and their usage
    ui->platformUsageQLabel->setText(platformText);
}

DetailDialog::~DetailDialog()
{
    delete ui;
}
