#include <QLabel>
#include <QHBoxLayout>
#include "handler/ui/ResultWidget.h"
#include "ui_ResultWidget.h"

ResultWidget::ResultWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResultWidget) {
    ui->setupUi(this);
    ui->imagesQScrollArea->setWidgetResizable(true);

    //The images (and their not aggregated results) need to be scrollable
    ui->imagesQWidgetContainer->setLayout(ui->imagesQVBoxLayout);
}

ResultWidget::~ResultWidget() {
    delete ui;
    clearLayout(ui->imagesQVBoxLayout);
//    if (ui->mainQHBoxLayout->itemAt(2)->layout()) {
//        clearLayout(ui->mainQHBoxLayout->itemAt(2)->layout());
//        delete ui->mainQHBoxLayout->itemAt(2);
//    }

    //TODO delete aggregated results layout
}

void ResultWidget::displayResults(ClassificationResult *classificationResult) {

    bool aggregated = false;

    //Checks if the results need to be displayed aggregated or not
    if (classificationResult->getAggregatedResults().size() > 0)
        aggregated = true;

    std::vector<ImageResult> results = classificationResult->getResults();

    for (unsigned int i = 0; i < results.size(); ++i) {
        ImageResult imageResult = results[i];

        //Creates a layout which display the file path and its image on top of each other
        QVBoxLayout *imageLayout = createImageLayout(imageResult.getImagePath());

        std::vector<std::pair<std::string, float>> result = imageResult.getResults();

        //Sorts the results so that the result with the highest float percentage gets displayed first
        result = sortVector(result);

        //A container is needed if the results are not aggregated; it will hold the image layout and possibly its result
        QHBoxLayout *container = new QHBoxLayout();
        container->addLayout(imageLayout);

        //If its not aggregated the individual result must be inside the QScrollArea
        if (!aggregated) {
            container->insertStretch(1);
            QVBoxLayout *resultLayout = createResultLayout(result);
            container->addLayout(resultLayout);
        }

        ui->imagesQVBoxLayout->addLayout(container);
        //TODO check if the size of the displayed picture, text etc. is alright
    }

    //Display the aggregated result outside of the QScrollArea
    if (aggregated) {
        std::vector<std::pair<std::string, float>> aggregatedResult = classificationResult->getAggregatedResults();
        QVBoxLayout *aggregatedLayout = createResultLayout(aggregatedResult);

        /* Places the aggregated result between two horizontal spacers in mainQHBoxLayout (index = 2) to avoid the
         * stretching of the result layout. */
        ui->mainQHBoxLayout->insertLayout(2, aggregatedLayout);
    }

    //Inserts a vertical stretch under the images to ensure that the image layouts are not stretched out.
    ui->imagesQVBoxLayout->insertStretch(-1);
}


QVBoxLayout *ResultWidget::createImageLayout(const std::string &filePath) {
    QVBoxLayout *imageLayout = new QVBoxLayout();
    imageLayout->insertStretch(0);
    //Displays the file path
    QLabel *filePathLabel = new QLabel(this);

    //TODO maybe QString attribute unnecessary (auto cast std::string to QString?)
    QString q_filePath = QString::fromStdString(filePath);

    //Removes the full path to the file and only returns the file name
    filePathLabel->setText(shortLink(filePath));
    imageLayout->addWidget(filePathLabel);

    //Displays the image
    QLabel *imageLabel = new QLabel(this);
    QImage image(q_filePath);
    imageLabel->setPixmap(QPixmap::fromImage(image).scaled(150, 150, Qt::KeepAspectRatio));
    imageLayout->addWidget(imageLabel);

    imageLayout->insertStretch(-1);
    return imageLayout;
}

QVBoxLayout *ResultWidget::createResultLayout(std::vector<std::pair<std::string, float>> &result) {
    QVBoxLayout *layout = new QVBoxLayout();

    //Stretch the layout from the top
    layout->insertStretch(0);
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
        layout->addWidget(topResult);
    }

    for (int i = 0; i < size; ++i) {
        std::pair<std::string, float> pair = result[i];

        //For every result insert a layout which has the result's name left and its percentage on the right side
        QHBoxLayout *labelLayout = new QHBoxLayout();

        QLabel *name = new QLabel(this);
        name->setText(QString::fromStdString(pair.first));
        name->setAlignment(Qt::AlignLeft);
        labelLayout->addWidget(name);

        QLabel *percentage = new QLabel(this);
        //TODO when percentage too long round the number
        percentage->setText((QString::number(pair.second) + "%"));
        percentage->setAlignment(Qt::AlignRight);
        labelLayout->addWidget(percentage);

        layout->addLayout(labelLayout);
    }

    //Stretch the layout from the bottom
    layout->insertStretch(-1);
    return layout;
}

QString ResultWidget::shortLink(const std::string &link) {
    QString output = QString::fromStdString(link);

    int slashIndex = output.lastIndexOf('/');

    //When lastIndexOf() returns -1 the char has not been found
    if (slashIndex != -1) {
        output.remove(0, slashIndex);
    }

    return output;
}

QString ResultWidget::shortPercentage(const float percentage, int floatingPoint){
    QString output = QString::number(percentage);
    //TODO implement this
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

QPushButton *ResultWidget::getDetailsQPushButton() {
    return ui->detailsQPushButton;
}

QPushButton *ResultWidget::getReturnQPushButton() {
    return ui->returnQPushButton;
}

QVBoxLayout *ResultWidget::getImagesQVBoxLayout() {
    return ui->imagesQVBoxLayout;
}

QHBoxLayout *ResultWidget::getMainQHBoxLayout() {
    return ui->mainQHBoxLayout;
}
