//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include <string>
#include "Wrapper.h"

class ImageWrapper : virtual public Wrapper {
private:
    std::string filepath;
public:
//    ImageWrapper(int numDimensions, int dimensionSizes, const std::vector &data,
//                 const std::string &filepath);

    const std::string &getFilepath() const;
};
