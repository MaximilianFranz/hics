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

    /**
     * @brief setCurrentWidget sets the given widget to the currently displayed one in mainWindowQStackedWidget, if it
     *        is stored in it.
     * @param widget is the to be displayed widget.
     */
    void setCurrentWidget(QWidget* widget);

private:
    Ui::MainWindow *ui;

    QStackedWidget* mainWindowQStackedWidget;
};
