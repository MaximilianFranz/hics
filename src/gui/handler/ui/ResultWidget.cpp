#include "handler/ui/ResultWidget.h"
#include "ui_ResultWidget.h"
#include "../NotImplementedException.h"

ResultWidget::ResultWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResultWidget)
{
    ui->setupUi(this);
    ui->imagesQWidgetContainer->setLayout(ui->imagesQVBoxLayout);
}

ResultWidget::~ResultWidget()
{
    delete ui;
}

void ResultWidget::displayResults(ClassificationResult &classificationResult){
    if(classificationResult.getAggregatedResults().size() == 0){
        //Not aggregated
        std::vector<ImageResult> results = classificationResult.getResults();

        for(int i = 0; i<results.size(); ++i){
            ImageResult imageResult = results[i];
            QVBoxLayout* imageLayout = new QVBoxLayout();

            QLabel* filePathLabel = new QLabel(this);

            QString filePath = QString::fromStdString(imageResult.getImagePath());
            filePathLabel->setText(filePath);
            imageLayout->addWidget(filePathLabel);

            QLabel* imageLabel = new QLabel(this);
            QImage image(filePath);
            imageLabel->setPixmap(QPixmap::fromImage(image).scaled(227, 227, Qt::KeepAspectRatio));
            imageLayout->addWidget(imageLabel);

            std::vector<std::pair<std::string, float>> result = imageResult.getResults();
            result = sortVector(result);


            QVBoxLayout* resultLayout = createResultLayout(result);

            QHBoxLayout* container = new QHBoxLayout();
            container->addLayout(imageLayout);
            container->addLayout(resultLayout);

            ui->imagesQVBoxLayout->addLayout(container);
            //TODO change this when results are added (results layout and image layout inside another layout) then add this layout to the imagesQVBoxLayout
            //ui->imagesQVBoxLayout->addLayout(imageLayout);

            //TODO add display for the results (percentages etc.)
            //TODO check if the size of the displayed picture, text etc. is alright
        }






    } else {
        //Aggregated

        //TODO implement display of aggregated results
    }
    ui->imagesQVBoxLayout->insertStretch(-1);

}

QVBoxLayout* ResultWidget::createResultLayout(std::vector<std::pair<std::string, float>> &result) {
    QVBoxLayout* layout = new QVBoxLayout();

    int size = result.size();

    if(size > 5){
        size = 5;
    }

    if(size != 0){
        QLabel* topResult = new QLabel();
        topResult->setText(QString::fromStdString(result.at(0).first));
        layout->addWidget(topResult);
    }

    for(int i = 0; i<size; ++i){
        std::pair<std::string, float> pair = result[i];

        QHBoxLayout* labelLayout = new QHBoxLayout();

        QLabel* name = new QLabel(this);
        name->setText(QString::fromStdString(pair.first));
        name->setAlignment(Qt::AlignLeft);
        labelLayout->addWidget(name);

        QLabel* percentage = new QLabel(this);
        //TODO when percentage too long round the number
        percentage->setText((QString::number(pair.second) + "%"));
        percentage->setAlignment(Qt::AlignRight);
        labelLayout->addWidget(percentage);

        layout->addLayout(labelLayout);

    }

    return layout;
}

std::vector<std::pair<std::string, float>> ResultWidget::sortVector(std::vector<std::pair<std::string, float>> &vector){

    for(int i = 0; i<vector.size(); ++i){
        std::pair<std::string, float>* pair_i = &vector[i];

        for (int j = 0; j<vector.size(); ++j){
            std::pair<std::string, float>* pair_j = &vector[j];

            if((i != j) && (pair_i->second > pair_j->second)){
                std::swap(*pair_i, *pair_j);
            }
        }
    }

    return vector;
}

QPushButton* ResultWidget::getDetailsQPushButton(){
    return ui->detailsQPushButton;
}

QPushButton* ResultWidget::getReturnQPushButton(){
    return ui->returnQPushButton;
}
