#include "handler/ui/MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

void MainWindow::createButton(){
    ui->pushButton->setText("It worked");
    this->show();
}

MainWindow::~MainWindow(){
    delete ui;
}
