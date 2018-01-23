//
// Created by David Culley on 07.01.18.
//

#include <loader/LabelLoader.h>
#include "NetBuilder.h"
#include "../NotImplementedException.h"

NeuralNet* NetBuilder::buildNeuralNet(NetInfo net) {
    std::string path ="../../../src/netbuilder/loader/models/alexnet.json";
    LayerMaker layerMaker;
    JSONModelLoader modelLoader(path);
    LayerConstructionParams lcp = modelLoader.getLayerConstructionParamsByIndex(0);
    InputLayer* inputLayer = layerMaker.createInputLayer(lcp);
    NeuralNet* alexNet = new NeuralNet(inputLayer, net);
    Layer* layer;
    for (int layerIndex = 1; layerIndex <= 21; layerIndex++) {
        lcp = modelLoader.getLayerConstructionParamsByIndex(layerIndex);
         std::vector<int> inputDimensionsForLayer = alexNet->getLastLayer()->getOutputDimensions();
        if (lcp.type == "conv"){
            layer = layerMaker.createConvLayer(lcp, inputDimensionsForLayer,NULL);
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
            layer = layerMaker.createFCLayer(lcp, inputDimensionsForLayer, NULL);
        }
        else {
            layer = layerMaker.createSoftmaxLossLayer(lcp, inputDimensionsForLayer);
        }
        alexNet->addLayer(layer);
    }

}

std::vector<NetInfo *> NetBuilder::queryAvailableNets() {
    throw NotImplementedException();
}

std::map<int, std::string> NetBuilder::getLabelMap(NetInfo net) {
    // Static return for now, later the we get paths from the ModelCrawler, maybe?
    return LabelLoader::getLabelMap("../../../src/netbuilder/loader/models/alexnet_labels.txt");
}
