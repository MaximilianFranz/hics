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

#include <QObject>
#include <ClassificationResult.h>
#include "MainWindowSubject.h"

/**
 * @class   Worker
 *
 * @brief   Worker is used to start a Classification in a new thread to keep the GUI responsive during computing intense
 *          tasks.
 *
 * Worker gets the observer objects from MainWindowHandler in the constructor and attaches them to itself, so that their
 * update method can be called. The work starts with the doWork method which will then emit the workDone signal when
 * finished and hands over the computed ClassificationResult.
 *
 * @author  Patrick Deubel
 * @date    24.02.2018
 *
 */
class Worker : public QObject, public MainWindowSubject {

    Q_OBJECT

public:

    /**
     * @brief The constructor initializes the Worker object by providing the needed observers on which the notify method
     *        shall be called.
     *
     * @param observers are the observers on the object from the main thread
     */
    explicit Worker(std::vector<ManagerObserver*> observers);

public slots:

    /**
     * @brief doWork will start the classification by calling notify on the observers.
     *
     * This function should be run in a worker thread to keep the GUI responsive.
     */
    virtual void doWork();

signals:

    /**
     * @brief The workDone signal gets emitted when the doWork() method is finished.
     *
     * workDone indicates that the classification has been finished.
     *
     * @param result is the computed ClassificationResult
     */
    void workDone(ClassificationResult* result);
};