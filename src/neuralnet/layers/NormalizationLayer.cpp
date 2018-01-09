//
// Created by Maximilian Franz on 07.01.18.
//

#include "NormalizationLayer.h"

bool NormalizationLayer::isPlatformSet() {
    return false;
}

void NormalizationLayer::forward(DataWrapper input, DataWrapper output) {

}

bool NormalizationLayer::isBiased() {
    return false;
}
