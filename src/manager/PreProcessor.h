//
// Created by jallmenroeder on 07/01/18.
//

#pragma once


#include <wrapper/ImageWrapper.h>
#include <map>
#include <QString>
#include <QImage>

/**
 * The PreProcessor converts the QImages from the GUI to ImageWrappers that can be used further down in the system.
 */
class PreProcessor {
private:
    //Output dimensions needed by the NeuralNet
    int width;      /*!< width of the images the neural net needs*/
    int height;     /*!< height of images the neural net needs*/

public:
    /**
     * Sets the output size
     * @param w     width
     * @param h     height
     */
    void setOutputSize(int w, int h);

    /**
     * Processes the input images from QImages to ImageWrappers that the System uses.
     * @param imgMap    Map containing the images
     * @return  vector with the images as ImageWrapper
     */
    std::vector<ImageWrapper*> processImages(std::map<QString, QImage> imgMap);
};
