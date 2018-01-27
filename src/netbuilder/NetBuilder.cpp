//
// Created by David Culley on 07.01.18.
//

#include <loader/LabelLoader.h>
#include <loader/weightloader/AlexNetWeightLoader.h>
#include <loader/JSONModelLoader.h>
#include <loader/ModelCrawler.h>

#include "NeuralNet.h"
#include "LayerMaker.h"

#include "NetBuilder.h"

NeuralNet* NetBuilder::buildNeuralNet(NetInfo netInfo) {
    // Use static path for now
    std::string path = MODEL_DIR + "/" + netInfo.getIdentifier() + ".json";
    LayerMaker layerMaker;
    JSONModelLoader modelLoader(path);
    LayerConstructionParams lcp = modelLoader.getLayerConstructionParamsByIndex(0);
    InputLayer* inputLayer = layerMaker.createInputLayer(lcp);
    // Use static path for now
    AlexNetWeightLoader loader("../../../src/netbuilder/loader/weightloader/alexnet_weights.h5");
    NeuralNet* alexNet = new NeuralNet(inputLayer, netInfo);
    Layer* layer;
    int weightIndex = 0;
    for (int layerIndex = 1; layerIndex <= 21; layerIndex++) {
        lcp = modelLoader.getLayerConstructionParamsByIndex(layerIndex);
         std::vector<int> inputDimensionsForLayer = alexNet->getLastLayer()->getOutputDimensions();
        if (lcp.type == "conv"){
            WeightWrapper weights = loader.getWeights(WeightLoader::LayerIdentifier(weightIndex));
            layer = layerMaker.createConvLayer(lcp, inputDimensionsForLayer, &weights);
            weightIndex++;
        }
            //Naive for now - No possibility for other activations
        else if (lcp.type == "activation") {
            layer = layerMaker.createReLuActivationLayer(lcp, inputDimensionsForLayer);
        }
        else if (lcp.type == "LRN") {
            layer = layerMaker.createLocalResponseNormLayer(lcp, inputDimensionsForLayer);
        }
        else if (lcp.type == "maxpooling") {
            layer = layerMaker.createMaxPoolLayer(lcp, inputDimensionsForLayer);
        }
            // Naive for now
        else if (lcp.type == "losslayer") {
            layer = layerMaker.createSoftmaxLossLayer(lcp, inputDimensionsForLayer);
        }
        else if (lcp.type == "fullyConnected") {
            WeightWrapper weights = loader.getWeights(WeightLoader::LayerIdentifier(weightIndex));
            layer = layerMaker.createFCLayer(lcp, inputDimensionsForLayer, &weights);
            weightIndex++;
        }
        else {
            layer = layerMaker.createSoftmaxLossLayer(lcp, inputDimensionsForLayer);
        }
        alexNet->addLayer(layer);
    }

    return alexNet;
}

std::vector<NetInfo *> NetBuilder::queryAvailableNets() {
    return ModelCrawler::getValidNets(MODEL_DIR);
}

std::map<int, std::string> NetBuilder::getLabelMap(NetInfo *net) {
    std::string labelpath = MODEL_DIR + "/" + net->getIdentifier() + "_labels.txt";
    return LabelLoader::getLabelMap(labelpath);
}
