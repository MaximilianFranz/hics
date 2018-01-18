#include "handler/ui/MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

void MainWindow::setCurrentWidget(QWidget &widget){
    int index = mainWindowQStackedWidget.indexOf(&widget);

    if(index >= 0){
        mainWindowQStackedWidget.setCurrentWidget(&widget);
    }
}

MainWindow::~MainWindow(){
    delete ui;
}
