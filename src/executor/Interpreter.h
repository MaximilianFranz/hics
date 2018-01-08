//
// Created by Maximilian Franz on 08.01.18.
//

#ifndef HICS_INTERPRETER_H
#define HICS_INTERPRETER_H

#include <map>
#include <string>

#include "ImageResult.h"
#include "../netbuilder/wrapper/DataWrapper.h"
#include "../netbuilder/wrapper/ImageWrapper.h"

class Interpreter {
public:
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
    void setLabels(std::map<int, std::string> labelMap);
};


#endif //HICS_INTERPRETER_H
