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
};
