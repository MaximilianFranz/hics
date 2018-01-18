#pragma once

#include <QWidget>
#include <list>
#include <NetInfo.h>

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

private:
    Ui::StartWidget *ui;
};
