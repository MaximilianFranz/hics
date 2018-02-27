/* Copyright 2018 The HICS Authors
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall
 * be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * SPDX-License-Identifier: MIT
 */

#include <algorithm>

#include <layers/weightlayers/ConvolutionLayer.h>
#include <layers/weightlayers/FullyConnectedLayer.h>
#include <layers/functionlayers/ReLUActivationLayer.h>
#include <layers/functionlayers/LocalResponseNormLayer.h>
#include <layers/functionlayers/SoftMaxLossLayer.h>
#include <layers/functionlayers/MaxPoolingLayer.h>

#include "PlatformPlacer.h"

PlatformPlacer::PlatformPlacer() {
    this->platformManager = &PlatformManager::getInstance();
}

// Is it useful to use more than two platforms (perfomance specific and fallback?)
void PlatformPlacer::placeComputations(NeuralNet *net, OperationMode mode, std::vector<PlatformInfo *> platforms) {

    compDistribution.clear();

    this->net = net;
    this->currentPlatforms = platforms;
    //TODO: Get only platforms previously selected!

    switch (mode) {
        case OperationMode::EnergyEfficient : placeEnergyEfficient();
            break;
        case OperationMode::LowPower : placeLowPower();
            break;
        case OperationMode::HighPower : placeHighPerformance();
            break;
        default: placeEnergyEfficient();
    }

}

std::vector<PlatformInfo*> PlatformPlacer::queryPlatforms() {
    return this->platformManager->getPlatformInfos();
}

const std::vector<std::pair<PlatformInfo *, float>> &PlatformPlacer::getCompDistribution() const {
    return compDistribution;
}


// PRIVATE METHODS

PlatformInfo* PlatformPlacer::getDefaultPlatform() {
    //Preferably use CPU as Default.
    for (auto pl : currentPlatforms) {
        if(pl->getType() == PlatformType::CPU) {
            return pl; //We assume for now that there always is a CPU platform!
        }
    }
    // If no CPU found, choose the first as default
    if (currentPlatforms.size() > 0)
        return currentPlatforms.front();
    else {
        return nullptr; // TODO: Make this an exception and handle it further up the hierarchy.
    }
}

//TODO: can we give a layer a attribute that specifies it's difficutly?
void PlatformPlacer::placeNetWith(PlatformInfo *perfomanceInfo, PlatformInfo *fallbackInfo) {
    int perfomanceCount = 0;
    int fallbackCount = 0;

    
    Platform *perfomance = platformManager->getPlatformById(perfomanceInfo->getPlatformId());
    Platform *fallback = platformManager->getPlatformById(fallbackInfo->getPlatformId());

    SimpleNetIterator *it = net->createIterator();
    do {
        Layer *currentLayer = it->getElement();
        if (currentLayer->getType() == LayerType::CONVOLUTION || currentLayer->getType() == LayerType::FULLYCONNECTED) {
            currentLayer->setPlatform(perfomance);
            perfomanceCount++;
        } else {
            currentLayer->setPlatform(fallback);
            fallbackCount++;
        }
        it->next();

    } while(it->hasNext());

    float layerCount = fallbackCount  + perfomanceCount;

    // Calculate simple distribution.
    if (fallbackInfo->getPlatformId() != perfomanceInfo->getPlatformId()) {
        compDistribution.push_back(std::pair<PlatformInfo *, float>(perfomanceInfo,
                                                                    perfomanceCount / layerCount));
        compDistribution.push_back(std::pair<PlatformInfo *, float>(fallbackInfo,
                                                                    fallbackCount / layerCount));
    } else {
        compDistribution.emplace_back(std::pair<PlatformInfo *, float>(perfomanceInfo, 1));
    }

}


//TODO: CHANGE ALL placeXYMode() to use PlatformInfo and get respective platforms from PfManager
void PlatformPlacer::placeLowPower() {
    PlatformInfo *fallback = getDefaultPlatform();
    PlatformInfo *performance = fallback;

    for (auto p : currentPlatforms) {
        if (p->getPowerConsumption() < performance->getPowerConsumption()) {
            performance = p;
        }
    }
    placeNetWith(performance, fallback);
}

void PlatformPlacer::placeEnergyEfficient() {
    PlatformInfo *fallback = getDefaultPlatform();
    PlatformInfo *performance = getDefaultPlatform();

    float currentBest = (performance->getFlops() / performance->getPowerConsumption());

    for (auto p : currentPlatforms) {
        float flops = p->getFlops();
        float power = p->getPowerConsumption();
        if (flops / power > currentBest) {
            performance = p;
            currentBest = flops / power;
        }
    }
    placeNetWith(performance, fallback);
}

void PlatformPlacer::placeHighPerformance() {
    PlatformInfo *fallback = getDefaultPlatform();
    PlatformInfo *performance = getDefaultPlatform();

    for (auto p : currentPlatforms) {
        if (p->getFlops() > performance->getFlops()) {
            performance = p;
        }
    }

    placeNetWith(performance, fallback);
}

