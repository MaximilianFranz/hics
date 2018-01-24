#pragma once

#include <QDialog>
#include <ClassificationResult.h>
#include <PerformanceData.h>
#include <PlatformInfo.h>

namespace Ui {
class DetailDialog;
}

class DetailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DetailDialog(QWidget *parent = 0);

    void insertDetails(const ClassificationResult* result);

    ~DetailDialog();

private:
    Ui::DetailDialog *ui;
};
