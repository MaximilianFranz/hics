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

#include <QtCore/QThread>
#include "Worker.h"
#include "MainWindowHandler.h"

MainWindowHandler::MainWindowHandler(std::vector<NetInfo *> &neuralNets, std::vector<PlatformInfo *> &platforms,
                                     std::vector<OperationMode> &operationModes) {

    //Initialize the used UI's
    mainWindow = new MainWindow();
    startWidget = new StartWidget(neuralNets, platforms, operationModes, mainWindow);
    resultWidget = new ResultWidget();
    detailDialog = new DetailDialog(mainWindow);

    //mainWindow's QStackedWidget will be the main display
    mainWindow->addWidgetToStack(startWidget);
    mainWindow->addWidgetToStack(resultWidget);

    mainWindow->setCurrentWidget(startWidget);

    connectAll();
}

void MainWindowHandler::setClassificationRequestState() {
    delete classificationRequestState;
    classificationRequestState = nullptr;

    NetInfo neuralNet = startWidget->getSelectedNeuralNet();
    std::vector<PlatformInfo> platforms = startWidget->getSelectedPlatforms();
    OperationMode mode = startWidget->getSelectedOperationMode();
    bool aggregate = startWidget->isAggregated();
    std::map<QString, QImage> userImgs = startWidget->getSelectedImages();

    if (!platforms.empty() && !userImgs.empty()) {
        classificationRequestState = new ClassificationRequest(neuralNet, platforms, mode, aggregate, userImgs);

        //Distribute the computation in a worker thread to ensure a responsive GUI
        auto *workerThread = new QThread;
        worker = new Worker(getObservers());
        worker->moveToThread(workerThread);

        connect(workerThread, &QThread::finished, worker, &QObject::deleteLater);

        //A signal must be connected to the workers method to ensure that the computation is run in the worker thread
        connect(this, &MainWindowHandler::startNotifying, worker, &Worker::doWork);

        //Receive the computed result
        connect(worker, &Worker::workDone, this, &MainWindowHandler::processClassificationResult);
        connect(worker, &Worker::exception, this, &MainWindowHandler::displayErrorMessage);

        //Delete memory
        connect(worker, &Worker::workDone, workerThread, &QThread::quit);
        connect(worker, &Worker::workDone, worker, &Worker::deleteLater);
        connect(worker, &Worker::workDone, workerThread, &QThread::deleteLater);

        workerThread->start();

        //Emit that the classification shall start
        emit startNotifying();

        //Displays a busy loading progress bar and disables all widgets
        startWidget->displayProgress();
    }
}

void MainWindowHandler::displayErrorMessage(const QString &errorMessage) {
    startWidget->resetProgressDisplay();
    startWidget->displayErrorMessage(errorMessage);
}

ClassificationRequest *MainWindowHandler::getClassificationRequestState() {
    return classificationRequestState;
}

void MainWindowHandler::processClassificationResult(ClassificationResult *classificationResult) {
    disconnectAll();
    mainWindow->removeWidgetFromStack(resultWidget);
    delete resultWidget;
    resultWidget = new ResultWidget;
    connectAll();
    //Initialize the results in resultWidget
    resultWidget->displayResults(classificationResult);
    mainWindow->addWidgetToStack(resultWidget);
    //Initialize the details in detailDialog
    detailDialog->insertDetails(classificationResult);
    //Change the currently displayed widget to resultWidget
    mainWindow->setCurrentWidget(resultWidget);
}

void MainWindowHandler::processReturnQPushButton() {
    //Enable the widgets in StartWidget again and remove the progress bar
    startWidget->resetProgressDisplay();

    mainWindow->setCurrentWidget(startWidget);

    disconnectAll();
    mainWindow->removeWidgetFromStack(resultWidget);
    delete resultWidget;

    resultWidget = new ResultWidget(mainWindow);
    mainWindow->addWidgetToStack(resultWidget);

    delete detailDialog;
    detailDialog = new DetailDialog(mainWindow);
    connectAll();
}

void MainWindowHandler::processDetailQPushButton() {
    detailDialog->show();
}

void MainWindowHandler::connectAll() {
    //Starts the classification
    connect(startWidget->getClassificationQPushButton(), SIGNAL(clicked(bool)), this,
            SLOT(setClassificationRequestState()));

    //Deletes resultWidget
    connect(resultWidget->getReturnQPushButton(), SIGNAL(clicked(bool)), this, SLOT(processReturnQPushButton()));

    //Opens the detailDialog
    connect(resultWidget->getDetailsQPushButton(), SIGNAL(clicked(bool)), this, SLOT(processDetailQPushButton()));

    //Resets detailDialog and resultWidget when resultWidget is destroyed; display startWidget
    connect(resultWidget, SIGNAL(destroyed()), this, SLOT(processReturnQPushButton())); //TODO Check if this works
}

void MainWindowHandler::disconnectAll() {
    disconnect(startWidget->getClassificationQPushButton(), SIGNAL(clicked()), this,
               SLOT(setClassificationRequestState()));
    disconnect(resultWidget->getReturnQPushButton(), SIGNAL(clicked()), this, SLOT(processReturnQPushButton()));
    disconnect(resultWidget->getDetailsQPushButton(), SIGNAL(clicked()), this, SLOT(processDetailQPushButton()));
    disconnect(resultWidget, SIGNAL(destroyed()), this, SLOT(processReturnQPushButton()));
}

MainWindowHandler::~MainWindowHandler() {
    disconnectAll();
    delete detailDialog;
    delete resultWidget;
    delete startWidget;
    delete mainWindow;
    delete classificationRequestState;
}

MainWindow *MainWindowHandler::getMainWindow() const {
    return mainWindow;
}

StartWidget *MainWindowHandler::getStartWidget() const {
    return startWidget;
}

ResultWidget *MainWindowHandler::getResultWidget() const {
    return resultWidget;
}

DetailDialog *MainWindowHandler::getDetailDialog() const {
    return detailDialog;
}
