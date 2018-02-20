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

#include "Executor.h"


Executor::Executor(std::string name)
        : Executor()
          {
    this->name = name;
}

Executor::Executor() {
    this->placer = (new PlatformPlacer());
    this->builder = (new NetBuilder());
    this->net = new NeuralNet(nullptr, createMockInfo());
}

std::vector<ImageResult*> Executor::classify(std::vector<ImageWrapper*> images,
                                             NetInfo netinfo,
                                             OperationMode mode,
                                            std::vector<PlatformInfo*> selectedPlatforms) {
    // Configure NeuralNet and Placer if settings have changed
    setupIfChanged(&netinfo, mode, selectedPlatforms);

    std::vector<ImageResult*> results;
    //Run classification for each image separately
    for (auto image : images) {
        ImageResult *r = classifyImage(image);
        results.push_back(r);
    }
    return results;
}

std::vector<PlatformInfo*> Executor::queryPlatform() {
    return placer->queryPlatforms();
}

std::vector<NetInfo*> Executor::queryNets() {
    return builder->queryAvailableNets();
}

ImageResult *Executor::classifyImage(ImageWrapper *image) {
    runDataForward(getImageData(image));
    auto outputData = net->getLastLayer()->getOutputWrapper();
    auto imageResult = interpreter->getResult(outputData, image, placer);
    net->reset();
    return imageResult;

}

void Executor::setupIfChanged(NetInfo *netInfo, OperationMode mode, std::vector<PlatformInfo *> &selectedPlatforms) {

    //Check if currently built net is correct!
    if(netInfo->getIdentifier() != this->net->getInfo().getIdentifier()) { //TODO: Overide == operator in NetInfo
        // free memory
        delete net;
        // create new NeuralNet as requested
        net = builder->buildNeuralNet(*netInfo);
        auto labelMap = builder->getLabelMap(netInfo);
        interpreter = new Interpreter(labelMap);
    }

    //Check if new placement is required
    if (currentMode != mode || selectedPlatforms != currentPlatforms) {
        placer->placeComputations(net, mode, selectedPlatforms);
    }
}

DataWrapper *Executor::getImageData(ImageWrapper *imageWrapper) {
    std::vector<float> imageData = imageWrapper->getData();
    return new DataWrapper(imageWrapper->getDimensions(), imageData);
}

void Executor::runDataForward(DataWrapper *data) {
    SimpleNetIterator* it = net->createIterator();
    // SET INPUT TO FIRST LAYER EXPLICITLY!
    it->getElement()->setInputWrapper(data);
    do {
        Layer *layer = it->getElement();
        layer->forward();
        layer->deleteGarbage();
        it->next();
    } while (it->hasNext());
}

const NetInfo Executor::createMockInfo() {
     NetInfo d("empty", 0, "empty");
    return d;
}

Executor::~Executor() {
    delete net;
    delete builder;
    delete placer;
    // Check if interpreter was set before deletion
    if (interpreter != nullptr) {
        delete interpreter;
    }
}

