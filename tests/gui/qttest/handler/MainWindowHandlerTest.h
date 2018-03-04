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

#include <QtTest/QTest>
#include <QObject>
#include <MultiTests.hh>
#include <OperationMode.h>
#include <PlatformInfo.h>
#include <NetInfo.h>
#include <handler/MainWindowHandler.h>

class MainWindowHandlerTest : public QObject {

Q_OBJECT

private:

    std::vector<NetInfo *> nets;
    std::vector<PlatformInfo *> platforms;
    std::vector<OperationMode> modes;

    MainWindowHandler *mainWindowHandler;

    ClassificationResult *classificationResult = nullptr;

    void setUpClassificationResult();

private slots:

    void initTestCase();

    void init();

    void cleanup();

    void testConstructor();

    void testStartClassification();

    void testDisplayClassification();

    void testReturnButton();

    void testDetailButton();
    
    void testUpdatePlatforms();

    void testAbortClassification();

    //void testSetClassificationRequestState();

};

TEST_DECLARE(MainWindowHandlerTest);