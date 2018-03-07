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

ImageResult * Interpreter::getResult(DataWrapper *output, ImageWrapper *originalImage, PlatformPlacer* placer) {
    std::vector<float> sortOut = output->getData();
    std::sort(sortOut.begin(), sortOut.end(), compareDesc); //sort output in descending order
    std::vector<std::pair<std::string, float>> results; // ordered list of labels and their probabilities
    if (output->getNumElements() <= TOP_X) {
        if (!labelMap.empty()) {
            for (int i = 0; i < output->getNumElements(); i++) {
                // insert only as many results as exist
                results.emplace_back(std::pair<std::string, float>(labelMap.at(getIndexOf(sortOut[i], output->getData())),
                                                            sortOut[i]));
            }
        }
        else {
            for (int i = 0; i < output->getNumElements(); i++) {
                // dont insert label, because non exist
                results.emplace_back(std::pair<std::string, float>("", sortOut[i]));
            }
        }
    }
    else {
        for (int i = 0; i < TOP_X; i++) {
            // Add Top 5 probabilities and their labels to the list.
            results.push_back(std::pair<std::string, float>(labelMap.at(getIndexOf(sortOut[i], output->getData())),
                                                            sortOut[i]));
        }
    }



    ImageResult *i = new ImageResult(results, placer->getCompDistribution(), *originalImage);

    // free data memory
    delete output;

    return i;
}

int Interpreter::getIndexOf(float value, std::vector<float> output) {
    auto index = distance(output.begin(), find(output.begin(), output.end(), value));
    if(index >= output.size()) {
        return -1; // value is not in vector
    } else {
        return static_cast<int>(index);
    }
}

const bool Interpreter::compareDesc(float a, float b) {
    return b < a;
}

