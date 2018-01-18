#pragma once

#include <QWidget>
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

    void addNeuralNets(std::list<NetInfo> &neuralNets);

    void addPlatforms(std::list<PlatformInfo> &platforms);

    void addOperationModes(std::list<OperationMode> &operationModes);

private:
    Ui::StartWidget *ui;
};
