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
    //Delete all allocated image layouts, result layouts
    clearLayout(ui->imagesQGridLayout);

    //Delete the aggregated result layout, if it exists
    clearLayout(ui->mainQHBoxLayout);

    for (ImageDisplay* i : imageDisplays) delete i;

    for (ResultDisplay* i : resultDisplays){
        for(ClassificationLabel* j : i->results) delete j;
        delete i;
    }

    //Delete the predefined ui
    delete ui;
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

    //Don't allow resizing of the images
    frame->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    return frame;
}

QFrame *
ResultWidget::createResultLayout(std::vector<std::pair<std::string, float>> &result, ResultDisplay *resultDisplay) {
    QFrame *frame = new QFrame(this);
    frame->setFrameShape(QFrame::Box);
    auto *layout = new QGridLayout(frame);

    //Display the Top result in red and above the others
    if (result.size() > 0) {
        QLabel *topResult = new QLabel(this);
        topResult->setStyleSheet("QLabel { color : red; }");
        topResult->setText(QString::fromStdString(result.at(0).first));
        layout->addWidget(topResult, 0, 0, 1, 1);
        resultDisplay->topResult = std::pair<std::string, QLabel *>(result.at(0).first, topResult);
    }

    for (unsigned long i = 0; i < result.size(); ++i) {
        std::pair<std::string, float> pair = result[i];

        QFontMetrics fontMetrics = QFontMetrics(QFont());

        QLabel *name = new QLabel(this);

        name->setText(QString::fromStdString(pair.first));
        name->setAlignment(Qt::AlignLeft);
        name->setToolTip(QString::fromStdString(pair.first));
        name->setToolTipDuration(-1);
        name->setTextInteractionFlags(Qt::TextSelectableByMouse);
        layout->addWidget(name, (int) (i + 1), 0);

        QLabel *percentage = new QLabel(this);
        //TODO when percentage too long round the number
        percentage->setText(QString::number(pair.second * 100) + "%");

        percentage->setAlignment(Qt::AlignRight);

        percentage->setStyleSheet("background:rgba(0, 0, 0, 0); border-right:"
                                  + QString::number(percentage->width() * pair.second)
                                  + "px solid " + PERCENTAGE_BAR_COLOR);
        percentage->setTextInteractionFlags(Qt::TextSelectableByMouse);

        layout->addWidget(percentage, (int) (i + 1), 1);

        name->setGeometry(QRect(0, 0, name->sizeHint().width(),
                                name->sizeHint().height())); /*!< Resizes the label to match the displayed text */

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
    //Resize every Result
    for (ResultDisplay* i : resultDisplays) {
        std::vector<ClassificationLabel *> classLabel = i->results;
        int sum = -1;

        //For every Top-5 the maximum width is used to display the percentages for every entry in the same ratio
        for (ClassificationLabel* j : classLabel) {
            int widthSum = j->nameDisplay->width() + j->percentageDisplay->width();
            if (widthSum > sum) {
                sum = widthSum;
            }
        }

        if (sum > 0) {
            auto nameTextSize = (int) ((sum / DENOMINATOR_TEXT_PERCENTAGE_RATIO) *
                                       NUMERATOR_TEXT_PERCENTAGE_RATIO);
            int percentageTextSize = sum - nameTextSize;

            for (ClassificationLabel* j : classLabel) {
                QFontMetrics fontMetrics = QFontMetrics(QFont());

                j->nameDisplay->setText(fontMetrics.elidedText(QString::fromStdString(j->name),
                                                                           Qt::TextElideMode::ElideMiddle,
                                                                           nameTextSize));
                j->percentageDisplay->setStyleSheet("background:rgba(0, 0, 0, 0); border-right:"
                                                                + QString::number
                                                                    (percentageTextSize * j->percentage)
                                                                + "px solid "
                                                                + PERCENTAGE_BAR_COLOR);
            }
        }
    }
}

void ResultWidget::resizeEvent(QResizeEvent *event) {
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
