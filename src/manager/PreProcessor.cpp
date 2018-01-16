//
// Created by jallmenroeder on 07/01/18.
//

#include "PreProcessor.h"

void PreProcessor::setOutputSize(int w, int h) {
    width = w;
    height = h;
}

std::vector<ImageWrapper> PreProcessor::processImages(std::map<QString, QImage> imgMap) {

    std::vector<ImageWrapper> images;

    //iterate over each image
    for (auto it = imgMap.begin(); it != imgMap.end(); ++it) {
        //cast QString to std::string
        std::string stdFilePath = it.operator*().first.toUtf8().constData();

        //scale QImage
        QImage currentImg = it.operator*().second;
        currentImg = currentImg.scaled(width, height, Qt::KeepAspectRatio);

        //init Wrapper
        std::vector<int> dim = {3, height, width};
        std::vector<float> bitmap;

        //create float bitmap, convention: {rgb, y, x}
        for (int rgb = 0; rgb < 3; ++rgb) {
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    float currentPixel;
                    switch (rgb) {
                        case 0:
                            currentPixel = currentImg.pixelColor(x, y).red();
                            break;
                        case 1:
                            currentPixel = currentImg.pixelColor(x, y).green();
                            break;
                        case 2:
                            currentPixel = currentImg.pixelColor(x, y).blue();
                            break;
                        default:
                            //TODO: specify exception
                            throw std::exception();
                    }
                    bitmap.push_back(currentPixel);
                }
            }
        }

        images.emplace_back(ImageWrapper(dim, bitmap, stdFilePath));
    }

    return images;
}
