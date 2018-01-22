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
    throw NotImplementedException();
}

QPushButton* ResultWidget::getDetailsQPushButton(){
    return ui->detailsQPushButton;
}

QPushButton* ResultWidget::getReturnQPushButton(){
    return ui->returnQPushButton;
}
