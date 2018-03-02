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

#include "ClassificationRequest.h"



ClassificationRequest::ClassificationRequest(NetInfo neuralNet, std::vector<PlatformInfo> platforms, OperationMode m,
                                             bool aggregate, std::map<QString, QImage> userImgs) :
        neuralNet(std::move(neuralNet)),
        platforms(std::move(platforms)),
        opMode(m), aggregate(aggregate), 
        userImages(std::move(userImgs)) {}



void ClassificationRequest::addUserImage(QString str, QImage img) {
    std::pair <QString, QImage> newImg(str, img);
    userImages.insert(newImg);
}

void ClassificationRequest::addPlatform(PlatformInfo platform) {
    platforms.push_back(platform);
}

void ClassificationRequest::removeUserImage(QString str) {
    userImages.erase(str);
}



//-----------------SETTER-----------------------------

void ClassificationRequest::setAggregateResults(bool aggregate) {
    this->aggregate = aggregate;
}

void ClassificationRequest::setSelectedOperationMode(OperationMode mode) {
    opMode = mode;
}

void ClassificationRequest::setSelectedNeuralNet(NetInfo net) {
    neuralNet = std::move(net);
}


//-----------------GETTER----------------------------

std::map<QString, QImage> ClassificationRequest::getUserImages() {
    return userImages;
}

std::vector<PlatformInfo*> ClassificationRequest::getSelectedPlatforms() {
    std::vector<PlatformInfo*> output;
    std::vector<PlatformInfo>::iterator it;

    for(it = platforms.begin(); it != platforms.end(); ++it){
        output.push_back(&(*it));
    }
    return output;
}

OperationMode ClassificationRequest::getSelectedOperationMode() {
    return opMode;
}

NetInfo ClassificationRequest::getSelectedNeuralNet() {
    return neuralNet;
}

bool ClassificationRequest::getAggregateResults() {
    return aggregate;
}
