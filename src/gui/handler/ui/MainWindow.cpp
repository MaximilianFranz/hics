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

#include <QSizePolicy>
#include <QtWidgets/QMessageBox>
#include <fstream>

#include "config.h"

#include "handler/ui/MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setWindowTitle("HICS");
    this->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    mainWindowQStackedWidget = new QStackedWidget(this);

    this->setCentralWidget(mainWindowQStackedWidget);

    auto menu = menuBar()->addMenu(tr("More"));
    auto action = new QAction("About", this);
    connect(action, &QAction::triggered, this, &MainWindow::openAboutBox);
    menu->addAction(action);
}

void MainWindow::init() {
    this->show();
}

void MainWindow::addWidgetToStack(QWidget *widget) {
    mainWindowQStackedWidget->addWidget(widget);
}

void MainWindow::removeWidgetFromStack(QWidget *widget) {
    mainWindowQStackedWidget->removeWidget(widget);
}

void MainWindow::setCurrentWidget(QWidget *widget) {
    int index = mainWindowQStackedWidget->indexOf(widget);

    //Check if widget is inside mainWindowQStackedWidget
    if (index >= 0) {
        mainWindowQStackedWidget->setCurrentWidget(widget);
    }
}

MainWindow::~MainWindow() {
    delete ui;
}


QStackedWidget *MainWindow::getMainWindowQStackedWidget() const {
    return mainWindowQStackedWidget;
}

void MainWindow::openAboutBox() {
    QMessageBox::about(this, "About", "HICS - Heterogenous Image Classification System\n\n"
        "Version: " PROJECT_VERSION "\n"
        "License: MIT\n\n"
        "Authors:\n"
        "Jan Allmenroeder <jallmenroeder@gmail.com>\n"
        "Michael Biebl <mbiebl@gmail.com>\n"
        "David Culley <david.culley@student.kit.edu>\n"
        "Patrick Deubel <patrick.deubel@gmail.com>\n"
        "Maximilian Franz <franzmaximilian1996@gmail.com>\n"
        "Kateryna Prokopenko <udewb@student.kit.edu>");
}
