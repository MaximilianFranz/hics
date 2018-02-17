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

#include <QLabel>
#include <QHBoxLayout>
#include "handler/ui/ResultWidget.h"
#include "ui_ResultWidget.h"

ResultWidget::ResultWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResultWidget) {
    ui->setupUi(this);
    ui->imagesQScrollArea->setWidgetResizable(true);
    ui->imagesQScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //The images (and their not aggregated results) need to be scrollable
    ui->imagesQWidgetContainer->setLayout(ui->imagesQGridLayout);
}

ResultWidget::~ResultWidget() {
    delete ui;
    clearLayout(ui->imagesQGridLayout);
//    if (ui->mainQHBoxLayout->itemAt(2)->layout()) {
//        clearLayout(ui->mainQHBoxLayout->itemAt(2)->layout());
//        delete ui->mainQHBoxLayout->itemAt(2);
//    }

    //TODO delete all allocated memory
}

void ResultWidget::displayResults(ClassificationResult *classificationResult) {

    bool aggregated = false;

    //Checks if the results need to be displayed aggregated or not
    if (!classificationResult->getAggregatedResults().empty())
        aggregated = true;

    std::vector<ImageResult> results = classificationResult->getResults();

    for (unsigned int i = 0; i < results.size(); ++i) {
        ImageResult imageResult = results[i];
        auto *imageDisplay = new ImageDisplay();
        imageDisplays.push_back(imageDisplay);
        imageDisplay->imageResult = &results[i];

        auto *resultDisplay = new ResultDisplay();
        resultDisplays.push_back(resultDisplay);
        resultDisplay->imageResult = &results[i];

        //Creates a layout which display the file path and its image on top of each other
        QFrame *imageLayout = createImageLayout(imageResult.getImagePath(), imageDisplay);

        std::vector<std::pair<std::string, float>> result = imageResult.getResults();

        //TODO remove sorting since results should already be sorted
        //Sorts the results so that the result with the highest float percentage gets displayed first
        result = sortVector(result);

        //If its not aggregated the individual result must be inside the QScrollArea
        if (!aggregated) {
            QFrame *resultLayout = createResultLayout(result, resultDisplay);
            ui->imagesQGridLayout->addWidget(resultLayout, i, 1);
        }

        ui->imagesQGridLayout->addWidget(imageLayout, i, 0);
        //TODO check if the size of the displayed picture, text etc. is alright
    }

    //Display the aggregated result outside of the QScrollArea
    if (aggregated) {
        auto *resultDisplay = new ResultDisplay();
        resultDisplays.push_back(resultDisplay);

        std::vector<std::pair<std::string, float>> aggregatedResult = classificationResult->getAggregatedResults();
        QFrame *aggregatedLayout = createResultLayout(aggregatedResult, resultDisplay);

        /* Places the aggregated result between two horizontal spacers in mainQHBoxLayout (index = 2) to avoid the
         * stretching of the result layout. */
        ui->mainQHBoxLayout->insertStretch(1);
        ui->mainQHBoxLayout->insertWidget(2, aggregatedLayout);
        ui->mainQHBoxLayout->insertStretch(3);
    }
}


QFrame *ResultWidget::createImageLayout(const std::string &filePath, ImageDisplay *imageDisplay) {
    QFrame *frame = new QFrame(this);
    frame->setFrameShape(QFrame::Box);

    auto *imageLayout = new QVBoxLayout(frame);
    imageLayout->insertStretch(0);

    //Displays the file path
    QLabel *filePathLabel = new QLabel(this);

    //TODO maybe QString attribute unnecessary (auto cast std::string to QString?)
    QString q_filePath = QString::fromStdString(filePath);

    filePathLabel->setToolTip(q_filePath);
    filePathLabel->setToolTipDuration(-1);

    //Removes the full path to the file and only returns the file name, shortens it if its larger than 150px
    QFontMetrics fontMetrics = QFontMetrics(QFont());
    filePathLabel->setText(fontMetrics.elidedText(shortLink(filePath), Qt::TextElideMode::ElideLeft, 150));
    imageLayout->addWidget(filePathLabel);

    //Displays the image
    QLabel *imageLabel = new QLabel(this);
    QImage image(q_filePath);
    imageLabel->setPixmap(QPixmap::fromImage(image).scaled(150, 150, Qt::KeepAspectRatio));
    imageLayout->addWidget(imageLabel);

    imageLayout->insertStretch(-1);

    imageDisplay->filePath = filePath;
    imageDisplay->filePathDisplay = filePathLabel;
    imageDisplay->imageDisplay = imageLabel;

    return frame;
}

QFrame *ResultWidget::createResultLayout(std::vector<std::pair<std::string, float>> &result, ResultDisplay* resultDisplay) {
    QFrame *frame = new QFrame(this);
    frame->setFrameShape(QFrame::Box);
    auto *layout = new QGridLayout(frame);

    int size = result.size();

    //TODO Maybe unnecessary since only Top5 ist stores in the ClassificaionResult
    //Only the Top-5 shall be displayed.
    if (size > 5) {
        size = 5;
    }

    //Display the Top result in red and above the others
    if (size != 0) {
        QLabel *topResult = new QLabel(this);
        topResult->setStyleSheet("QLabel { color : red; }");
        topResult->setText(QString::fromStdString(result.at(0).first));
        layout->addWidget(topResult, 0, 0, 0, -1, Qt::AlignTop);
        resultDisplay->topResult = std::pair<std::string, QLabel*>(result.at(0).first, topResult);
    }

    for (int i = 0; i < size; ++i) {
        std::pair<std::string, float> pair = result[i];

        QFontMetrics fontMetrics = QFontMetrics(QFont());

        QLabel *name = new QLabel(this);
        //TODO Change 350 either to const attribute or a calculated ratio
        name->setText(QString::fromStdString(pair.first));
        name->setAlignment(Qt::AlignLeft);
        name->setToolTip(QString::fromStdString(pair.first));
        name->setToolTipDuration(-1);
        name->setTextInteractionFlags(Qt::TextSelectableByMouse);

        layout->addWidget(name, i+1, 0);

        QLabel *percentage = new QLabel(this);
        //TODO when percentage too long round the number
        percentage->setText(QString::number(pair.second * 100) + "%");
        percentage->setAlignment(Qt::AlignRight);

        percentage->setStyleSheet("background:rgba(0, 0, 0, 0); border-right:"
                                  + QString::number(percentage->width() * pair.second)
                                  + "px solid " + PERCENTAGE_BAR_COLOR);
        percentage->setTextInteractionFlags(Qt::TextSelectableByMouse);

        layout->addWidget(percentage, i+1, 1);

        auto *classificationLabel = new ClassificationLabel();
        classificationLabel->name = pair.first;
        classificationLabel->nameDisplay = name;
        classificationLabel->percentage = pair.second;
        classificationLabel->percentageDisplay = percentage;

        resultDisplay->results.push_back(classificationLabel);
    }

    return frame;
}

QString ResultWidget::shortLink(const std::string &link) {
    QString output = QString::fromStdString(link);

    int slashIndex = output.lastIndexOf('/');

    //When lastIndexOf() returns -1 the char has not been found
    if ((slashIndex != -1) && (output.size() >= (slashIndex + 1))) {
        output.remove(0, slashIndex + 1);
    }

    return output;
}

std::vector<std::pair<std::string, float>>
ResultWidget::sortVector(std::vector<std::pair<std::string, float>> &vector) {

    for (unsigned int i = 0; i < vector.size(); ++i) {
        std::pair<std::string, float> *pair_i = &vector[i];

        for (unsigned int j = 0; j < vector.size(); ++j) {
            std::pair<std::string, float> *pair_j = &vector[j];

            if ((i != j) && (pair_i->second > pair_j->second)) {
                std::swap(*pair_i, *pair_j);
            }
        }
    }

    return vector;
}

void ResultWidget::clearLayout(QLayout *layout) {
    QLayoutItem *item;

    //Removes every item inside the layout and delete it
    while ((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
            delete item->widget();
        }
    }
}

void ResultWidget::resize() {
    for(unsigned int i = 0; i < resultDisplays.size(); ++i){
        std::vector<ClassificationLabel*> classLabel = resultDisplays[i]->results;
        for(unsigned int j = 0; j < classLabel.size(); ++j){
            //TODO fix resizing when widget is resized, currently sizeHint stays the same even when resizing, thus the widget does not get resized dynamically
            int widthSum = classLabel[j]->percentageDisplay->sizeHint().width() + classLabel[j]->nameDisplay->sizeHint().width();
            int labelSize = (int) ((widthSum/3)*2); //TODO make ratio const attribute for easy change
            int percentageSize = widthSum - labelSize;

            QFontMetrics fontMetrics = QFontMetrics(QFont());
            classLabel[j]->nameDisplay->setStyleSheet("background:red");

            classLabel[j]->nameDisplay->setText(fontMetrics.elidedText(QString::fromStdString(classLabel[j]->name),
                                                                       Qt::TextElideMode::ElideMiddle,
                                                                       labelSize));
            classLabel[j]->percentageDisplay->setStyleSheet("background:rgba(0, 0, 0, 0); border-right:"
                                                            + QString::number(percentageSize * classLabel[j]->percentage)
                                                            + "px solid " + PERCENTAGE_BAR_COLOR);
        }
    }
}

void ResultWidget::resizeEvent(QResizeEvent *event) {
    //TODO Resize the displayed images
    resize();
    QWidget::resizeEvent(event);
}

QPushButton *ResultWidget::getDetailsQPushButton() {
    return ui->detailsQPushButton;
}

QPushButton *ResultWidget::getReturnQPushButton() {
    return ui->returnQPushButton;
}

QGridLayout *ResultWidget::getImagesQGridLayout() {
    return ui->imagesQGridLayout;
}

QHBoxLayout *ResultWidget::getMainQHBoxLayout() {
    return ui->mainQHBoxLayout;
}
