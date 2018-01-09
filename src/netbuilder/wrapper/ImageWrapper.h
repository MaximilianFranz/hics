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
    const std::string &getFilepath() const;

    int getNumDimensions() override;

    int getDimensionSizes() override;
};
