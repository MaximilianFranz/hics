//
// Created by pselab on 31.01.18.
//

#pragma once

#include <QtTest/QTest>
#include <QObject
#include <handler/ui/DetailDialog.h>


class DetailDialogTest : public QObject {

Q_OBJECT

private:

    DetailDialog* detailDialog = nullptr;

private slots:

    void initTestCase();

    void init();

    void cleanup();

};

