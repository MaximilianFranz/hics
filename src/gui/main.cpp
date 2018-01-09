//
// Created by Patrick Deubel on 08.01.18.
//

#include <QApplication>
#include "handler/ui/MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow h;
    h.show();

    return a.exec();
}
