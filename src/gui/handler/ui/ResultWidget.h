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

/**
 * @class ResultWidget
 *
 * @brief ResultWidget is a custom QWidget and is used to display the result page of the GUI.
 *
 * ResultWidget inherits QWidget and is therefore also a custom QWidget. It represents the result page of the GUI, that
 * is, when a classification is finished and the user wants to see the classified image and the Top-5 probability to
 * which labels the images match.
 *
 * It provides an interface for MainWindowHandler to abstract away the Qt objects from the rest of the software. The
 * method displayResults() can be called with a ClassificationResult as parameter which will then initialize the user
 * interface of ResultWidget with the needed data.
 *
 * @author Patrick Deubel
 */
class ResultWidget : public QWidget {

    Q_OBJECT

public:

    /**
     * @brief The standard constructor initializes the ResultWidget
     *
     * It makes the QScrollArea resizable, which later holds the images and their (not aggregated) results and assings
     * the image layout to its container.
     *
     * @param parent is an optional parent widget
     */
    explicit ResultWidget(QWidget *parent = 0);

    ~ResultWidget();

    void displayResults(const ClassificationResult &classificationResult);

    std::vector<std::pair<std::string, float>> sortVector(std::vector<std::pair<std::string, float>> &vector);

    QPushButton* getDetailsQPushButton();

    QPushButton* getReturnQPushButton();

private:

    Ui::ResultWidget *ui;

    QString shortLink(const std::string &link);

    QVBoxLayout* createImageLayout(const std::string &filePath);

    QVBoxLayout* createResultLayout(std::vector<std::pair<std::string, float>> &result);
};
