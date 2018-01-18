//
// Created by Patrick Deubel on 08.01.18.
//

#include <QApplication>
#include "handler/ui/MainWindow.h"
#include "handler/MainWindowHandler.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindowHandler h;

    return a.exec();
}
