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

#include <algorithm>

#include "Interpreter.h"
#include <PlatformPlacer.h>

Interpreter::Interpreter(std::map<int, std::string> &labelMap)
        :labelMap(labelMap)
{

}

//TODO: Faster way to match the top 5 results back to their original positing in output
ImageResult * Interpreter::getResult(DataWrapper *output, ImageWrapper *originalImage, PlatformPlacer* placer) {
    std::vector<float> sortOut = output->getData();
    std::sort(sortOut.begin(), sortOut.end(), compareDesc); //sort output in descending order
    std::vector<std::pair<std::string, float>> results; // ordered list of labels and their probabilities
    for (int i = 0; i < TOP_X; i++) {
        // Add Top 5 probabilities and their labels to the list.
        results.push_back(std::pair<std::string, float>(labelMap.at(getIndexOf(sortOut[i], output->getData())),
                                                        sortOut[i]));
    }

    ImageResult *i = new ImageResult(results, placer->getCompDistribution(), *originalImage);
    return i;
}

void Interpreter::setLabels(std::map<int, std::string> &labelMap) {
    this->labelMap = labelMap;
}


int Interpreter::getIndexOf(float value, std::vector<float> output) {
    for (int i = 0; i < output.size() ; i++) {
        if(output[i] == value) {
            return i;
        }
    }
    return 0;
}

const bool Interpreter::compareDesc(float a, float b) {
    return b < a;
}

