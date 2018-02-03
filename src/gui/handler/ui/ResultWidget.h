#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <ClassificationResult.h>

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

    /**
     * @brief Destructor for ResultWidget
     *
     * Delets the ui and all its child widgets, as well as all allocated memory in ResultWidget.
     */
    ~ResultWidget();

    /**
     * @brief displayResults() takes a ClassificationResult and displays its results in the ResultWidget
     *
     * displayResults() displays the images and their file path together with its classification results. If the results
     * are aggregated, only the images and their file paths are displayed in the scroll widget and next to it the
     * aggregated result.
     * If the results are not aggregated, every image gets displayed together with its result in the scroll widget.
     *
     * @param classificationResult has the classification results
     */
    void displayResults(ClassificationResult *classificationResult);

    /**
     * @brief Returns the QPushButton used to display the details
     * @return the detailsQPushButton
     */
    QPushButton *getDetailsQPushButton();

    /**
     * @brief Returns the QPushButton used to return to the starting page of the GUI
     * @return the returnQPushButton
     */
    QPushButton *getReturnQPushButton();

    /**
     * @brief getImagesQVBoxLayout returns the layout in which the images and their results are stored
     * @return imagesQVBoxLayout
     */
    //QVBoxLayout *getImagesQVBoxLayout();

    /**
     * @brief getMainQHBoxLayout returns the main layout of ResultWidget
     * @return mainQHBoxLayout
     */
    QHBoxLayout *getMainQHBoxLayout();

private:

    Ui::ResultWidget *ui;

    QString shortLink(const std::string &link);

    QString shortPercentage(const float percentage, int floatingPoint);

    QVBoxLayout *createImageLayout(const std::string &filePath);

    QVBoxLayout *createResultLayout(std::vector<std::pair<std::string, float>> &result);

    std::vector<std::pair<std::string, float>> sortVector(std::vector<std::pair<std::string, float>> &vector);

    void clearLayout(QLayout *layout);
};
