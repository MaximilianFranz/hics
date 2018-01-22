#include "handler/ui/ResultWidget.h"
#include "ui_ResultWidget.h"
#include "../NotImplementedException.h"

ResultWidget::ResultWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResultWidget)
{
    ui->setupUi(this);
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
            ImageResult imageResult = results.at(i);
            QVBoxLayout* imageLayout = new QVBoxLayout(this);

            QLabel* imageLabel = new QLabel(this);
            QLabel* filePathLabel = new QLabel(this);
            QString filePath = QString::fromStdString(imageResult.getImagePath());
            QImage image(filePath);

            imageLabel->setPixmap(QPixmap::fromImage(image).scaled(227, 227, Qt::KeepAspectRatio));
            filePathLabel->setText(filePath);

            imageLayout->addWidget(filePathLabel);
            imageLayout->addWidget(imageLabel);

            //TODO change this when results are added (results layout and image layout inside another layout) then add this layout to the imagesQVBoxLayout
            ui->imagesQVBoxLayout->addLayout(imageLayout);

            //TODO add display for the results (percentages etc.)
            //TODO check if the size of the displayed picture, text etc. is alright
        }






    } else {
        //Aggregated

        //TODO implement display of aggregated results
    }
}

QPushButton* ResultWidget::getDetailsQPushButton(){
    return ui->detailsQPushButton;
}

QPushButton* ResultWidget::getReturnQPushButton(){
    return ui->returnQPushButton;
}
