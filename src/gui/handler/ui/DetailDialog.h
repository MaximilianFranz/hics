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

#include <QDialog>
#include <QLabel>
#include <ClassificationResult.h>

namespace Ui {
class DetailDialog;
}

/**
 * @class DetailDialog
 *
 * @brief DetailDialog is a custom QDialog and is used to display the details of a classification.
 *
 *
 * DetailDialog inherits QDialog. It is used to represent the detail page of the classification in the GUIModule.
 * It provides an interface to MainWindowHandler, the method insertDetails(), which will take a ClassificationResult as
 * parameter and display the results in the called DetaiDialog.
 *
 * In a DetailDialog, the user can see the consumed power and time as well as how much a selected platform has been
 * used for the classification.
 *
 * @author Patrick Deubel
 */

class DetailDialog : public QDialog
{
    Q_OBJECT

public:

    /**
     * @brief The standard constructor initializes a DetaiDialog object
     * @param parent is an optional parent widget
     */
    explicit DetailDialog(QWidget *parent = 0);

    /**
     * @brief insertDetails() displays the details given by the ClassificationResult parameter
     *
     * insertDetails() populates the QLabels from DetailDialog's design file with the details given by the
     * ClassificationResult parameter.
     *
     * @param result is the ClassificationResult which holds the details
     */
    void insertDetails(const ClassificationResult* result);

    /**
     * Destructor of DetaiDialog which deletes all allocated memory on the heap.
     */
    ~DetailDialog();

    QLabel* getComputationTimeQLabel();

    QLabel* getPowerConsumptionQLabel();

    QLabel* getPlatformUsageQLabel();

private:
    Ui::DetailDialog *ui;

    const QString COMPUTATION_TIME_UNIT = "ms";
    const QString POWER_CONSUMPTION_UNIT = "Ws";
};
