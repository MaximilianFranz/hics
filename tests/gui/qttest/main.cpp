//
// Created by pselab on 03.02.18.
//

#include <QtTest/QTest>
#include <QApplication>
#include <handler/MainWindowHandlerTest.h>
#include <handler/ui/StartWidgetTest.h>
#include <handler/ui/ResultWidgetTest.h>
#include <handler/ui/DetailDialogTest.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindowHandlerTest test1;
    StartWidgetTest test2;
    ResultWidgetTest test3;
    DetailDialogTest test4;

    QTest::qExec(&test1, argc, argv);
    QTest::qExec(&test2, argc, argv);
    QTest::qExec(&test3, argc, argv);
    QTest::qExec(&test4, argc, argv);

    return a.exec();
}