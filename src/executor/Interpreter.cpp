//
// Created by Maximilian Franz on 08.01.18.
//

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

