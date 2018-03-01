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
    AlexNetWeightLoader loader(RES_DIR "weights/alexnet_weights.h5");
    NeuralNet* alexNet = new NeuralNet(inputLayer, netInfo);
    Layer* layer;
    int weightIndex = 0;
    for (int layerIndex = 1; layerIndex <= 21; layerIndex++) {
        lcp = modelLoader.getLayerConstructionParamsByIndex(layerIndex);
         std::vector<int> inputDimensionsForLayer = alexNet->getLastLayer()->getOutputDimensions();
        if (lcp.type == "conv"){
            WeightWrapper *weights = loader.getWeights(WeightLoader::LayerIdentifier(weightIndex));
            layer = layerMaker.createConvLayer(lcp, inputDimensionsForLayer, weights);
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
            WeightWrapper *weights = loader.getWeights(WeightLoader::LayerIdentifier(weightIndex));
            layer = layerMaker.createFCLayer(lcp, inputDimensionsForLayer, weights);
            weightIndex++;
        }
        else {
            layer = layerMaker.createSoftmaxLossLayer(lcp, inputDimensionsForLayer);
        }
        alexNet->addLayer(layer);
    }

    return alexNet;
}

std::vector<NetInfo*> NetBuilder::queryAvailableNets() {
    return ModelCrawler::getValidNets(MODEL_DIR);
}

const map<int, string> NetBuilder::getLabelMap(NetInfo *net) {
    std::string labelpath = MODEL_DIR + "/" + net->getIdentifier() + "_labels.txt";
    return LabelLoader::getLabelMap(labelpath);
}
