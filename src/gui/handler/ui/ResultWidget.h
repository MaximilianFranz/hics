#pragma once

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "ClassificationResult.h"

namespace Ui {
class ResultWidget;
}

class ResultWidget : public QWidget {

    Q_OBJECT

public:

    explicit ResultWidget(QWidget *parent = 0);

    ~ResultWidget();

    void displayResults(ClassificationResult &classificationResult);

    std::vector<std::pair<std::string, float>> sortVector(std::vector<std::pair<std::string, float>> &vector);

    QPushButton* getDetailsQPushButton();

    QPushButton* getReturnQPushButton();

private:

    Ui::ResultWidget *ui;

    QString shortLink(const std::string &link);

    QVBoxLayout* createResultLayout(std::vector<std::pair<std::string, float>> &result);
};
