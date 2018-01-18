#include "handler/ui/MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralwidget = &mainWindowQStackedWidget; //TODO check if this is enough to full screen mainWindowQStackedWidget
}

void MainWindow::addWidgetToStack(QWidget &widget){
    mainWindowQStackedWidget.addWidget(&widget);
}

void MainWindow::setCurrentWidget(QWidget &widget){
    int index = mainWindowQStackedWidget.indexOf(&widget);

    //Check if widget is inside mainWindowQStackedWidget
    if(index >= 0){
        mainWindowQStackedWidget.setCurrentWidget(&widget);
    }
}

MainWindow::~MainWindow(){
    delete ui;
}
