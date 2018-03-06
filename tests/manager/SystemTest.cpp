//
// Created by jallmenroeder on 06/03/18.
//

#include <Manager.h>
#include <QtWidgets/QApplication>
#include "SystemTest.h"

SCENARIO("System Test") {
    SECTION("Complete Test") {
        char *argv[] = {"program name", "arg1", "arg2", NULL};
        int argc = sizeof(argv) / sizeof(char*) - 1;
        QApplication a(argc, argv);

        Manager manager;
        manager.initGUI();
        a.exec();
    }
}