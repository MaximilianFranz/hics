//
// Created by Patrick Deubel on 08.01.18.
//

#include <QApplication>
#include <Manager.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


   Manager manager;
   manager.initGUI();




    return a.exec();
}
