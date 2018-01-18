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
     * @param dimensions
     * @param filepath
     * @see Wrapper
     */
    ImageWrapper(std::vector<int> &dimensions, std::string filepath);
    /**
     * Create ImageWrapper from existing data vector
     *
     * @param numDimensions
     * @param dimensions
     * @param data
     * @param filepath
     */
    ImageWrapper(std::vector<int> dimensions, std::vector<float> &data, std::string filepath);

    /**
     * Get path to the original image this wrapper represents
     *
     * @return path to the image on the hard drive
     */
    const std::string getFilepath() const;
};
