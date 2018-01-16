//
// Created by Maximilian Franz on 08.01.18.
//

#pragma once

#include <map>
#include <string>

#include "ImageResult.h"
#include "../netbuilder/wrapper/DataWrapper.h"
#include "../netbuilder/wrapper/ImageWrapper.h"

class Interpreter {
private:
    std::map<int, std::string> labelMap;

    int getIndexOf(float value, std::vector<float> output);

public:

    /**
     * Use top-x results for prediction result.
     */
    const int TOP_X = 5; //By convention from the ILSRVC we use 5

    Interpreter(std::map<int, std::string> &labelMap);

    /**
     * \brief maps the output of the network to the labels and returns an ImageResult
     *
     * @param output of the last layer of the neural net
     * @param originalImage original input which resulted in the output
     * @return ImageResult containing the top 5 labels and their probabilities.
     */
    ImageResult getResult(DataWrapper output, ImageWrapper originalImage);

    /**
     * \brief sets the labels to map the number of an output neuron to its corresponding label
     *
     * @param labelMap Map of all labels the NeuralNet can classify
     * @see NetBuilder
     */
    void setLabels(std::map<int, std::string> &labelMap);

    static const bool compareDesc(float a, float b);

};
