//
// Created by Maximilian Franz on 08.01.18.
//

#pragma once


#include <string>
#include <map>
#include <wrapper/ImageWrapper.h>


class ImageResult {
private:
    ImageWrapper image;
public:
    std::map<float, std::string> results; // ordered list of labels and their probabilities

    /**\brief Constructor
     *
     * @param results
     */
    ImageResult(const std::map<float, std::string> &results, ImageWrapper &image);

    /**
     *
     * @return path to the image that was classified
     */
    std::string getImagePath();

};

