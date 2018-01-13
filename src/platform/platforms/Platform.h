//
// Created by David Culley on 13.01.18.
//

#pragma once

#include <layerfunctions/LayerFunction.h>

#include <string>
#include <PlatformInfo.h>

class Platform {
protected:
    PlatformInfo platformInfo;

public:
    virtual LayerFunction &createFunction(std::string layerType) = 0;

    const PlatformInfo &getPlatformInfo() const;
};
