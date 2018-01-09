#include "handler/ui/ResultWidget.h"
#include "ui_ResultWidget.h"

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
