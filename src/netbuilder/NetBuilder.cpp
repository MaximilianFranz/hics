//
// Created by David Culley on 07.01.18.
//

#include <loader/LabelLoader.h>
#include <loader/weightloader/AlexNetWeightLoader.h>
#include "NetBuilder.h"
#include "../NotImplementedException.h"


NeuralNet* NetBuilder::buildNeuralNet(NetInfo net) {
    // Use static path for now
    std::string path ="../../../src/netbuilder/loader/models/alexnet.json";
    LayerMaker layerMaker;
    JSONModelLoader modelLoader(path);
    LayerConstructionParams lcp = modelLoader.getLayerConstructionParamsByIndex(0);
    InputLayer* inputLayer = layerMaker.createInputLayer(lcp);
    // Use static path for now
    AlexNetWeightLoader loader("../../../src/netbuilder/loader/weightloader/alexnet_weights.h5");
    NeuralNet* alexNet = new NeuralNet(inputLayer, net);
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
        else if (lcp.type == "activation") {
            layer = layerMaker.createReLuActivationLayer(lcp, inputDimensionsForLayer);
        }
        else if (lcp.type == "LRN") {
            layer = layerMaker.createLocalResponseNormLayer(lcp, inputDimensionsForLayer);
        }
        else if (lcp.type == "maxpooling") {
            layer = layerMaker.createMaxPoolLayer(lcp, inputDimensionsForLayer);
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

}

std::vector<NetInfo *> NetBuilder::queryAvailableNets() {
    // STATIC ALEXNET for now!
    std::vector<NetInfo*> availableNets;
    NetInfo *alexnet = new NetInfo("alexnet", 227);
    availableNets.push_back(alexnet);
    return availableNets;
}

std::map<int, std::string> NetBuilder::getLabelMap(NetInfo net) {
    // Static return for now, later the we get paths from the ModelCrawler, maybe?
    return LabelLoader::getLabelMap("../../../src/netbuilder/loader/models/alexnet_labels.txt");
}
