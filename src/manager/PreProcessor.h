//
// Created by jallmenroeder on 07/01/18.
//

#pragma once


#include <wrapper/ImageWrapper.h>
#include <map>
#include <QString>
#include <QImage>

class PreProcessor {
private:
    //Output dimensions needed by the NeuralNet
    int width;
    int height;

public:
    /**
     * Sets the output size
     * @param w
     * @param h
     */
    void setOutputSize(int w, int h);

    /**
     * Processes the input images from QImages to ImageWrappers that the System uses.
     * @param imgMap
     * @return
     */
    std::vector<ImageWrapper> processImages(std::map<QImage, QString> imgMap);
};
