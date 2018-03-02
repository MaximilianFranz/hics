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

#include <QThread>
#include <ClassificationResult.h>
#include "handler/MainWindowHandler.h"

class MainWindowHandler; /*!< Forward declaration for MainWindowHandler */

/**
 * @class   WorkerThread
 *
 * @brief   WorkerThread is used to start a Classification in a new thread to keep the GUI responsive during computing
 *          intense tasks.
 *
 * WorkerThread gets the MainWindowHandler object in the constructor and attaches them to itself, so that its notify
 * method can be called in a separate thread. The work startsin the overrided run method which will then emit the
 * resultReady signal when finished and hands over the computed ClassificationResult.
 *
 * @author  Patrick Deubel
 * @date    24.02.2018
 *
 */
class WorkerThread : public QThread {

    Q_OBJECT

    /**
     * @brief run will start the classification by calling notify on the mainWindowHandler
     *
     * This function should be run in a worker thread to keep the GUI responsive.
     */
    void run() Q_DECL_OVERRIDE;

private:

    MainWindowHandler *mWH = nullptr;

public:

    /**
    * @brief The constructor initializes the WorkerThread object by providing the needed observers on which the notify
    *        method shall be called.
    *
    * @param mWH is the MainWindowHandler object which wants to run its notfiy method in a separate thread
    */
    explicit WorkerThread(MainWindowHandler *mWH);

signals:

    /**
    * @brief The resultReady signal gets emitted when the run() method is finished.
    *
    * resultReady indicates that the classification has been finished.
    *
    * @param result is the computed ClassificationResult
    */
    void resultReady(ClassificationResult* result);

};