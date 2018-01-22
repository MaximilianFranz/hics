#pragma once

#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QImage>
#include <QPixmap>
#include <QMap>
#include <QFileDialog>
#include <list>
#include <map>
#include <vector>
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
    explicit StartWidget(std::list<NetInfo> &neuralNets, std::list<PlatformInfo> &platforms,
                                      std::list<OperationMode> &operationModes, QWidget *parent = 0);

    ~StartWidget();

    void addNeuralNet(const QString &neuralNet);

    void addPlatform(const QString &platform);

    void addOperationMode(const QString &operationMode);

    QHBoxLayout* addInputImage(QImage* image);

    NetInfo getSelectedNeuralNet();

    std::vector<PlatformInfo> getSelectedPlatforms();

    bool isAggregated();

    QPushButton* getClassificationQPushButton();
public slots:

    void processInputImageButton();

    void processConfirmDeletionButton();

    void processAbortDeletionQPushButton();

private:
    Ui::StartWidget *ui;

    QList<QHBoxLayout*> inputImagesLayouts;

    QMap<QImage*, QHBoxLayout*> images;

    std::map<QString, NetInfo> neuralNetMap;
    std::map<QString, PlatformInfo> platformMap;

    void addNeuralNets(std::list<NetInfo> &neuralNets);

    void addPlatforms(std::list<PlatformInfo> &platforms);

    void addOperationModes(std::list<OperationMode> &operationModes);

    void clearLayout(QLayout *layout);


};
