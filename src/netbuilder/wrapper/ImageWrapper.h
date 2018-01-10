//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <string>
#include "Wrapper.h"

class ImageWrapper : public Wrapper {
private:
    std::string filepath;

public:
    /**
     * Create empty ImageWrapper
     *
     * @param numDimensions
     * @param dimensionSizes
     * @param filepath
     * @see Wrapper
     */
    ImageWrapper(int numDimensions, std::vector<int> &dimensionSizes, std::string filepath)
            : Wrapper(numDimensions, dimensionSizes), filepath(filepath){
    }

    /**
     * Create ImageWrapper from existing data vector
     *
     * @param numDimensions
     * @param dimensionSizes
     * @param data
     * @param filepath
     */
    ImageWrapper(int numDimensions, std::vector<int> dimensionSizes, std::vector<float> &data, std::string filepath)
            : Wrapper(numDimensions, dimensionSizes, data), filepath(filepath){
    }

    std::string getFilepath() {
        return filepath;
    }

};
