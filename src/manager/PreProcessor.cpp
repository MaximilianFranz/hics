/* Copyright 2018 The HICS Authors
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall
 * be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 */

#include <iostream>
#include "PreProcessor.h"

void PreProcessor::setOutputSize(int w, int h) {
    width = w;
    height = h;
}

std::vector<ImageWrapper*> PreProcessor::processImages(std::map<QString, QImage> imgMap) {

    std::vector<ImageWrapper*> images;

    //iterate over each image
    for (auto it = imgMap.begin(); it != imgMap.end(); ++it) {
        //cast QString to std::string
        std::string stdFilePath = it.operator*().first.toUtf8().constData();

        //scale QImage
        QImage currentImg = it.operator*().second;

        currentImg = currentImg.scaled(width, height, Qt::KeepAspectRatio);

        //init Wrapper
        std::vector<int> dim = {3, height, width};
        std::vector<float> bitmap(3*height*width);

        double meanR = 0;
        double meanG = 0;
        double meanB = 0;

        int index = 0;

        //create float bitmap, convention: {rgb, y, x}
        //-- OUTPUT IS IN BGR format -- X and Y are swapped for some reason!
        for (int bgr = 0; bgr < 3; bgr++) {
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    float currentPixel = 0;
                    //Fill image with black pixels if dimension is wrong
                    if (y >= currentImg.width() || x >= currentImg.height()) {
                        currentPixel = 0;
                    }
                    else {
                        //extract the right RGB channel
                        switch (bgr) {
                            case 2:
                                currentPixel = qRed(currentImg.pixel(y, x));
                                meanR += currentPixel / (height * width);
                                break;
                            case 1:
                                currentPixel = qGreen(currentImg.pixel(y, x));
                                meanG += currentPixel / (height * width);
                                break;
                            case 0:
                                currentPixel = qBlue(currentImg.pixel(y, x));
                                meanB += currentPixel / (height * width);
                                break;
                            default:
                                //TODO: specify exception
                                throw std::exception();
                        }
                    }
                    bitmap[index] = (currentPixel);
                    index++;
                }
            }
        }

        //substract mean to normalize
        for (int i = 0; i < bitmap.size(); i++) {
            bitmap[i] = float(bitmap[i] - (meanR + meanG + meanB)/3);
        }

        images.emplace_back(new ImageWrapper(dim, bitmap, stdFilePath));

    }

    return images;
}
