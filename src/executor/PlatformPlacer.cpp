//
// Created by Maximilian Franz on 08.01.18.
//

#include <layers/weightlayers/ConvolutionLayer.h>
#include <layers/weightlayers/FullyConnectedLayer.h>
#include <layers/functionlayers/ReLUActivationLayer.h>
#include <layers/functionlayers/LocalResponseNormLayer.h>
#include <layers/functionlayers/SoftMaxLossLayer.h>
#include <layers/functionlayers/MaxPoolingLayer.h>
#include <NotImplementedException.h>
#include "PlatformPlacer.h"

PlatformPlacer::PlatformPlacer() {
    this->platformManager = &PlatformManager::getInstance();
}

std::vector<PlatformInfo *> PlatformPlacer::queryPlatforms() {
    return this->platformManager->getPlatformInfos();
}

// Is it useful to use more than two platforms (perfomance specific and fallback?)
void PlatformPlacer::placeComputations(NeuralNet *net, OperationMode mode, std::vector<PlatformInfo *> platforms) {

    this->currentMode = mode;
    this->net = net;
    this->currentPlatformsInfos = platforms;
    //TODO: Get only platforms previously selected!
    this->currentPlatforms = platformManager->getPlatforms();

    switch (mode) {
        case OperationMode::EnergyEfficient : placeEnergyEfficient();
        case OperationMode::LowPower : placeLowPower();
        case OperationMode::HighPower : placeHighPerformance();
        default: ; //TODO: Default impl.
    }

}

//void PlatformPlacer::default_setLayerFunctionForLayer(Layer *pLayer) {
//    auto *pl = getDefaultPlatform();
//    if(pLayer->getType() == LayerType::CONVOLUTION) {
//        auto *c = dynamic_cast<ConvolutionLayer*>(pLayer);
//        c->setFunction(pl->createConvolutionFunction());
//    }
//    else if(pLayer->getType() == LayerType::FULLYCONNECTED) {
//        auto *c = dynamic_cast<FullyConnectedLayer*>(pLayer);
//        c->setFunction(pl->createFullyConnectedFunction());
//    }
//    else if(pLayer->getType() == LayerType::ACTIVATION_RELU) {
//        auto *c = dynamic_cast<ReLUActivationLayer*>(pLayer);
//        c->setFunction(pl->createActivationFunction(LayerType::ACTIVATION_RELU));
//    }
//    else if(pLayer->getType() == LayerType::NORMALIZATION_LOCALRESPONSE) {
//        auto *c = dynamic_cast<LocalResponseNormLayer*>(pLayer);
//        c->setFunction(pl->createResponseNormalizationFunction(LayerType::NORMALIZATION_LOCALRESPONSE));
//    }
//    else if(pLayer->getType() == LayerType::LOSS_SOFTMAX) {
//        auto *c = dynamic_cast<SoftMaxLossLayer*>(pLayer);
//        c->setFunction(pl->createLossFunction(LayerType::LOSS_SOFTMAX));
//    }
//    else if(pLayer->getType() == LayerType::POOLING_MAX) {
//        auto *c = dynamic_cast<MaxPoolingLayer*>(pLayer);
//        c->setFunction(pl->createPoolingFunction(LayerType::POOLING_MAX));
//    }
//    else {
//        // Nothing todo for Naive Layers
//    }
//
//}

Platform* PlatformPlacer::getDefaultPlatform() {
    for (auto pl : currentPlatforms) {
        if(pl->getPlatformType() == PlatformType::CPU) {
            return pl; //We assume for now that there always is a CPU platform!
        }
    }
    return nullptr;
}

//TODO: can we give a layer a attribute that specifies it's difficutly?
// So that we don't hard-code which layers are "difficult"
void PlatformPlacer::placeNetWith(Platform *perfomance, Platform *fallback) {
    int perfomanceCount = 0;
    int fallbackCount = 0;
    SimpleNetIterator *it = net->createIterator();
    do {
        Layer *currentLayer = it->getElement();
        if (currentLayer->getType() == LayerType::CONVOLUTION || currentLayer->getType() == LayerType::FULLYCONNECTED) {
            placeLayerWith(perfomance, currentLayer);
            perfomanceCount++;
        } else if (currentLayer->getType() == LayerType::INPUT || currentLayer->getType() == LayerType::CONCAT){

            fallbackCount++; //Naive layers are computed on CPU
            it->next();
            continue; // Nothing to do

        } else {

            placeLayerWith(fallback, currentLayer);
            fallbackCount++;

        }
        it->next();

    } while(it->hasNext());

    int layerCount = fallbackCount  + perfomanceCount;
    // Calculate simple distribution.
    if (fallback->getPlatformInfo().getPlatformId() != perfomance->getPlatformInfo().getPlatformId()) {
        compDistribution.push_back(std::pair<PlatformInfo *, float>(&perfomance->getPlatformInfo(),
                                                                    perfomanceCount / layerCount));
        compDistribution.push_back(std::pair<PlatformInfo *, float>(&fallback->getPlatformInfo(),
                                                                    fallbackCount / layerCount));
    } else {
        compDistribution.emplace_back(std::pair<PlatformInfo *, float>(&perfomance->getPlatformInfo(), 1));
    }

}


//TODO: CHANGE ALL placeXYMode() to use PlatformInfo and get respective platforms from PfManager
void PlatformPlacer::placeLowPower() {
    Platform *fallback = getDefaultPlatform();
    Platform *performance = getDefaultPlatform();

    for (auto p : currentPlatforms) {
        if (p->getPlatformInfo().getPowerConsumption() < performance->getPlatformInfo().getPowerConsumption()) {
            performance = p;
        }
    }
    placeNetWith(performance, fallback);
}

void PlatformPlacer::placeEnergyEfficient() {
    Platform *fallback = getDefaultPlatform();
    Platform *performance = getDefaultPlatform();

    //TODO:
//    float currentBest = (performance->getPlatformInfo().getFlops() / performance->getPlatformInfo().getPowerConsumption());

    float currentBest = 5;

    for (auto p : currentPlatforms) {
        float flops = p->getPlatformInfo().getFlops();
        float power = p->getPlatformInfo().getPowerConsumption();
        if (flops / power > currentBest) {
            performance = p;
            currentBest = flops / power;
        }
    }
    placeNetWith(performance, fallback);
}

void PlatformPlacer::placeHighPerformance() {
    Platform *fallback = getDefaultPlatform();
    Platform *performance = getDefaultPlatform();

    for (auto p : currentPlatforms) {
        if (p->getPlatformInfo().getFlops() > performance->getPlatformInfo().getFlops()) {
            performance = p;
        }
    }
    placeNetWith(performance, fallback);

}

// TODO: Change architecture such that layers get platforms via a setPlatform()
// method and create the function they need within the layer
void PlatformPlacer::placeLayerWith(Platform *pl, Layer *pLayer) {

    if(pLayer->getType() == LayerType::CONVOLUTION) {
        auto *c = dynamic_cast<ConvolutionLayer*>(pLayer);
        c->setFunction(pl->createConvolutionFunction());
    }
    else if(pLayer->getType() == LayerType::FULLYCONNECTED) {
        auto *c = dynamic_cast<FullyConnectedLayer*>(pLayer);
        c->setFunction(pl->createFullyConnectedFunction());
    }
    else if(pLayer->getType() == LayerType::ACTIVATION_RELU) {
        auto *c = dynamic_cast<ReLUActivationLayer*>(pLayer);
        c->setFunction(pl->createActivationFunction(LayerType::ACTIVATION_RELU));
    }
    else if(pLayer->getType() == LayerType::NORMALIZATION_LOCALRESPONSE) {
        auto *c = dynamic_cast<LocalResponseNormLayer*>(pLayer);
        c->setFunction(pl->createResponseNormalizationFunction(LayerType::NORMALIZATION_LOCALRESPONSE));
    }
    else if(pLayer->getType() == LayerType::LOSS_SOFTMAX) {
        auto *c = dynamic_cast<SoftMaxLossLayer*>(pLayer);
        c->setFunction(pl->createLossFunction(LayerType::LOSS_SOFTMAX));
    }
    else if(pLayer->getType() == LayerType::POOLING_MAX) {
        auto *c = dynamic_cast<MaxPoolingLayer*>(pLayer);
        c->setFunction(pl->createPoolingFunction(LayerType::POOLING_MAX));
    }
}

const std::vector<std::pair<PlatformInfo *, float>> &PlatformPlacer::getCompDistribution() const {
    return compDistribution;
}
