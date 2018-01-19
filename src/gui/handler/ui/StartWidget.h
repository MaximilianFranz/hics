#pragma once

#include <QWidget>
#include <QPushButton>
#include <list>
#include <NetInfo.h>
#include <PlatformInfo.h>
#include <OperationMode.h>

namespace Ui {
class StartWidget;
}

class StartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StartWidget(QWidget *parent = 0);

    ~StartWidget();

    void addNeuralNet(const QString &neuralNet);

    void addPlatform(const QString &platform);

    void addOperationMode(const QString &operationMode);

    QPushButton* getSelectInputImagesQPushButton();

private:
    Ui::StartWidget *ui;
};
