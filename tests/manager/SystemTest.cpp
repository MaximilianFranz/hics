/* Copyright 2018 The HICS Authors
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall
 * be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 */

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