//
// Created by pselab on 31.01.18.
//
#pragma once

#include <QtTest/QTest>
#include <QObject>
#include <handler/ui/ResultWidget.h>

class ResultWidgetTest : public QObject {

Q_OBJECT

private:

    ResultWidget *resultWidget = nullptr;

    ClassificationResult *classificationResult = nullptr;

    std::string getActualString(int index, int layoutIndex, bool aggregated);

private slots:

    void initTestCase();

    void init();

    void cleanup();

    void testNotAggregated();

    void testAggregated();
};
