//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include "ModelLoader.h"

class JSONModelLoader: public ModelLoader {
public:
    string getNetWorkName() override;

};

string JSONModelLoader::getNetWorkName() {
    return nullptr;
}
