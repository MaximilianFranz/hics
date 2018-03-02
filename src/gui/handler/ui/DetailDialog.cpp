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

#include <PerformanceData.h>
#include <PlatformInfo.h>
#include "DetailDialog.h"
#include "ui_DetailDialog.h"

DetailDialog::DetailDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DetailDialog) {
    ui->setupUi(this);
    this->setWindowTitle("Details");
}

void DetailDialog::insertDetails(const ClassificationResult *result) {
    ui->computationTimeCaptionQLabel->setText("Computation time for "
                                              + QString::number(result->getResults().size())
                                              + " classified image(s):");

    //Display the computation time.
    ui->computationTimeQLabel->setText(QString::number(result->getPerformance().getComputationTime())
                                       + " "
                                       + COMPUTATION_TIME_UNIT);

    //Display the power consumption
    ui->powerConsumptionQLabel->setText(QString::number(result->getPerformance().getPowerConsumption())
                                        + " "
                                        + POWER_CONSUMPTION_UNIT);

    std::vector<std::pair<PlatformInfo *, float>> platformUsage = result->getPerformance().getPlatformUsage();

    //Add the used platforms and their usage to a QString
    QString platformText = "";
    for (int i = 0; i < platformUsage.size(); ++i) {
        std::pair<PlatformInfo *, float> pair = platformUsage[i];
        platformText +=
            QString::fromStdString(pair.first->getDescription()) + ": " + QString::number(qRound(pair.second * 100)) +
            "%, ";
    }

    //Remove the last white space and comma from the QString
    if (platformText.size() > 0) {
        platformText.remove((platformText.size() - 2), 2);
    }

    //Display the platforms and their usage
    ui->platformUsageQLabel->setText(platformText);
}

DetailDialog::~DetailDialog() {
    this->close();
    delete ui;
}

QLabel *DetailDialog::getComputationTimeQLabel() {
    return ui->computationTimeQLabel;
}

QLabel *DetailDialog::getPowerConsumptionQLabel() {
    return ui->powerConsumptionQLabel;
}

QLabel *DetailDialog::getPlatformUsageQLabel() {
    return ui->platformUsageQLabel;
}