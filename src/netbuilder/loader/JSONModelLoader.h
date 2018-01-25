//
// Created by Maximilian Franz on 07.01.18.
//

#pragma once

#include "JSONModelLoader.h"
#include "ModelLoader.h"

class JSONModelLoader: public ModelLoader {
public:
    JSONModelLoader(string path);
    void init();
    string getNetWorkName() override;
    string getNetWorkID() override;
    int getRequiredDimension() override;
    string getLayerTypeByIndex(int index) override;
    LayerConstructionParams getLayerConstructionParamsByIndex(int index) override;

    json getLayerJSON(int index);

    bool isValid();
};
