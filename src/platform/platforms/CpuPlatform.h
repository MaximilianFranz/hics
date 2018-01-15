//
// Created by David Culley on 12.01.18.
//

#pragma once

#include "Platform.h"

class CpuPlatform : public Platform {
public:
    LayerFunction &createFunction(std::string layerType) override;
};
