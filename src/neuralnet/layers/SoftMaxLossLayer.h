//
// Created by Maximilian Franz on 07.01.18.
//

#ifndef HICS_SOFTMAXLOSSLAYER_H
#define HICS_SOFTMAXLOSSLAYER_H


#include "Layer.h"

class SoftMaxLossLayer : public Layer {
public:
    void forward(DataWrapper input, DataWrapper output) override;

    bool isPlatformSet() override;

    bool isBiased() override;
};


#endif //HICS_SOFTMAXLOSSLAYER_H
