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
