//
// Created by jallmenroeder on 06/03/18.
//

#include <Manager.h>
#include <QtWidgets/QApplication>
#include "SystemTest.h"

SCENARIO("System Test") {
    SECTION("Complete Test") {
        char *argv[] = {(char*)"HICS-TEST", (char *)"arg1", (char *)"arg2", (char *)0};
        int argc = sizeof(argv) / sizeof(char*) - 1;
        QApplication a(argc, argv);

        Manager manager = Manager();
        manager.initGUI();
        a.exec();

        rename(RES_DIR "computationHosts.json", RES_DIR "c.json");
        manager = Manager();
        manager.initGUI();
        a.exec();
        rename(RES_DIR "c.json",RES_DIR "computationHosts.json");

        rename(RES_DIR "models/alexnet.json", RES_DIR "models/c.json");
        manager = Manager();
        manager.initGUI();
        a.exec();
        rename(RES_DIR "models/c.json", RES_DIR "models/alexnet.json");
    }
}