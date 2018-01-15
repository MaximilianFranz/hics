//
// Created by David Culley on 13.01.18.
//

#pragma once

#include <layerfunctions/LayerFunction.h>

#include <string>
#include <PlatformInfo.h>

enum PlatformType {
    CPU,
    FPGA,
    GPU,
};

class Platform {
protected:
    PlatformInfo platformInfo;

public:
    virtual LayerFunction &createFunction(std::string layerType) = 0;

    virtual const PlatformInfo &getPlatformInfo() const = 0;

    virtual PlatformType getPlatformType() = 0;
};
