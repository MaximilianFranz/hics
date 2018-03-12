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

#include <map>
#include <string>
#include <wrapper/DataWrapper.h>

#include "ImageResult.h"

class PlatformPlacer;

class Interpreter {
private:
    std::map<int, std::string> labelMap;

    int getIndexOf(float value, std::vector<float> output);

public:

    /**
     * Use top-x results for prediction result. CHANGE THIS if more than the top 5 are wanted!
     */
    static const int TOP_X = 5; //By convention from the ILSRVC we use 5

    /**
     * Constructor passing the required labelMap
     *
     * @param labelMap containing labels used to interpret results
     */
    explicit Interpreter(std::map<int, std::string> &labelMap);

    /**
     * \brief maps the output of the network to the labels and returns an ImageResult
     *
     * @param output of the last layer of the neural net
     * @param originalImage original input which resulted in the output
     * @return ImageResult containing the top 5 labels and their probabilities.
     */
    ImageResult* getResult(DataWrapper *output, ImageWrapper *originalImage, PlatformPlacer* placer);

    /**
     * Custom comparator for std::sort
     *
     * @param a float
     * @param b float
     * @return whether a is bigger than b
     */
    static const bool compareDesc(float a, float b);

};
