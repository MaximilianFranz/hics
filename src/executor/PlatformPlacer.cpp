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
    // Better as pointer or directly as reference like:
//    this->platformManager = PlatformManager::getInstance();
    this->platformManager = &PlatformManager::getInstance();

}

std::vector<PlatformInfo *> PlatformPlacer::queryPlatforms() {
    return this->platformManager->getPlatformInfos();
}

// Currently OperationMode ist not considered and we resort to the CPUPlatform for testing
void PlatformPlacer::placeComputations(NeuralNet *net, OperationMode mode, std::vector<PlatformInfo *> platforms) {
    SimpleNetIterator *it = net->createIterator();

    this->currentPlatforms = platformManager->getPlatforms();

    while(it->hasNext()) {
        if (!it->getElement()->isLayerFunctionSet()) {
            default_setLayerFunctionForLayer(it->getElement()); //Use fallback for now
        }
        it->next();
    }

    // Making sure the placer knows the current state of the net
    this->currentMode = mode;
    this->net = net;
    this->currentPlatformsInfos = platforms;

}

//TODO: Currently there is no way around this dynamic_cast ...

void PlatformPlacer::default_setLayerFunctionForLayer(Layer *pLayer) {
    auto *pl = getDefaultPlatform();
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
    else {
        // Nothing todo for Naive Layers
    }

}

Platform* PlatformPlacer::getDefaultPlatform() {
    for (auto pl : currentPlatforms) {
        if(pl->getPlatformType() == PlatformType::CPU) {
            return pl; //We assume for now that there always is a CPU platform!
        }
    }
}
