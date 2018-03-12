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
#include <IllegalArgumentException.h>

#include "PlatformPlacer.h"

PlatformPlacer::PlatformPlacer() {
    this->platformManager = &PlatformManager::getInstance();
}

// Is it useful to use more than two platforms (perfomance specific and fallback?)
void PlatformPlacer::placeComputations(NeuralNet *net, OperationMode mode, std::vector<PlatformInfo *> platforms) {

    compDistribution.clear();

    this->net = net;
    this->currentPlatforms = std::move(platforms);

    switch (mode) {
        case OperationMode::EnergyEfficient : placeEnergyEfficient();
            break;
        case OperationMode::LowPower : placeLowPower();
            break;
        case OperationMode::HighPower : placeHighPerformance();
            break;
            // Omit default, because all cases are caught
            // method cannot be called with illegal OperationMode argument
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
    if (! currentPlatforms.empty()) {
        for (auto pl : currentPlatforms) {
            if(pl->getType() == PlatformType::CPU) {
                //We assume for now that there always is a CPU platform!
                return pl;
            }
        }
        // If no CPU found, choose the first as default
        return currentPlatforms.front();
    }
    else {
        throw IllegalArgumentException("No platforms selected, can't compute without platforms");
    }
}

void PlatformPlacer::placeNetWith(PlatformInfo *performanceInfo, PlatformInfo *fallbackInfo) {
    float performanceDifficulty = 0;
    float  fallbackDifficulty = 0;

    long long totalDifficulty = net->getTotalDifficulty();
    long long averageDifficulty = totalDifficulty / net->getNumLayers();
    
    Platform *performance = platformManager->getPlatformById(performanceInfo->getPlatformId());
    Platform *fallback = platformManager->getPlatformById(fallbackInfo->getPlatformId());

    SimpleNetIterator *it = net->createIterator();
    do {
        Layer *currentLayer = it->getElement();

        // If layer is relatively difficult, use the performance platform
        if (currentLayer->getDifficulty() > averageDifficulty) {
            currentLayer->setPlatform(performance);
            performanceDifficulty += currentLayer->getDifficulty();
        } else {
            currentLayer->setPlatform(fallback);
            fallbackDifficulty += currentLayer->getDifficulty();
        }
        it->next();

    } while(it->hasNext());

    float performanceDistribution = performanceDifficulty / totalDifficulty;
    float fallbackDistribution = fallbackDifficulty / totalDifficulty;

    // Calculate distribution.
    if (fallbackInfo->getPlatformId() != performanceInfo->getPlatformId()) {
        compDistribution.emplace_back(performanceInfo, performanceDistribution);
        compDistribution.emplace_back(fallbackInfo, fallbackDistribution);
    } else {
        compDistribution.emplace_back(std::pair<PlatformInfo *, float>(performanceInfo, 1));
    }

    // Add platforms that have not been used for completeness of the details tab.
    for (auto p : currentPlatforms) {
        // Platform selected but not used for placement
        if (p->getPlatformId() != performanceInfo->getPlatformId()
            && p->getPlatformId() != fallbackInfo->getPlatformId()) {
            compDistribution.emplace_back(std::pair<PlatformInfo *, float>(p, 0));
        }
    }
}


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

