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

#pragma once

#include <QMainWindow>
#include <QStackedWidget>

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class is the main window of the GUI. It's current widget can be changed so that custom widgets
 *        can be displayed.
 *
 * The MainWindow class inherits QMainWindow. It represents the main window of the GUI and consists of the
 * mainWindowQStackedWidget which can display one QWidget at a time. MainWindow provides a public slot to add and change
 * the current widget. MainWindowHandler is responsible for handling it.
 *
 * @author Patrick Deubel
 */
class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    /**
     * @brief addWidgetToStack adds the given widget to mainWindowQStackedWidget.
     * @param widget is the to be added widget
     */
    void addWidgetToStack(QWidget* widget);

    void removeWidgetFromStack(QWidget* widget);

    /**
     * @brief setCurrentWidget sets the given widget to the currently displayed one in mainWindowQStackedWidget, if it
     *        is stored in it.
     * @param widget is the to be displayed widget.
     */
    void setCurrentWidget(QWidget* widget);

    /**
     * @brief getMainWindowQStackedWidget returns the QStackedWidget which holds the to be displayed widgets and is the
     *        main display of the GUI.
     * @return mainWindowQStackedWidget
     */
    QStackedWidget *getMainWindowQStackedWidget() const;

private:

    Ui::MainWindow *ui;

    QStackedWidget* mainWindowQStackedWidget;

public slots:

    void openAboutBox();
};
