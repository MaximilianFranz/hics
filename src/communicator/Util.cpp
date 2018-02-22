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

#include "Util.h"

void Util::imageWrapperToMessage(const ImageWrapper *img, ImageWrapperMessage *messagePtr) {
    messagePtr->set_filepath(img->getFilepath());
    for (int dim : img->getDimensions()) {
        messagePtr->add_dimensions(dim);
    }

    //Every pixel in the float array has to be added individually
    for (float pixel : img->getData()) {
        messagePtr->add_data(pixel);
    }
}

void Util::netInfoToMessage(NetInfo* net, NetInfoMessage *messagePtr) {
    messagePtr->set_name(net->getName());
    messagePtr->set_identifier(net->getIdentifier());
    messagePtr->set_imagedimension(net->getImageDimension());
}

void Util::platformInfoToMessage(const PlatformInfo *platform, PlatformInfoMessage *messagePtr) {
    messagePtr->set_description(platform->getDescription());
    switch (platform->getType()) {
        case PlatformType::CPU  : messagePtr->set_type(PlatformInfoMessage::CPU);
            break;
        case PlatformType::FPGA : messagePtr->set_type(PlatformInfoMessage::FPGA);
            break;
        case PlatformType::GPU  : messagePtr->set_type(PlatformInfoMessage::GPU);
            break;
    }
    messagePtr->set_platformid(platform->getPlatformId());
    messagePtr->set_powerconsumption(platform->getPowerConsumption());
    messagePtr->set_flops(platform->getFlops());
}

void Util::imageResultToMessage(const ImageResult *result, ImageResultMessage *resultPtr) {
    //convert image
    imageWrapperToMessage(&(result->getImage()), resultPtr->mutable_image());

    //convert result labels
    for (auto labelIt : result->getResults()) {
        LabelMessage* newLabel = resultPtr->add_classification();
        newLabel->set_name(labelIt.first);
        newLabel->set_probability(labelIt.second);
    }

    //convert computationDistribution
    for (auto distributionIt : result->getCompDistribution()) {
        PlatformDistributionMessage* newDistribution = resultPtr->add_platformdistribution();
        platformInfoToMessage(distributionIt.first, newDistribution->mutable_platform());
        newDistribution->set_usage(distributionIt.second);
    }
}

ImageWrapper* Util::messageToImageWrapper(const ImageWrapperMessage *imgMes) {
    //read dimensions
    std::vector<int> dimensions;
    for (int i = 0; i < imgMes->dimensions_size(); i++) {
        dimensions.push_back(imgMes->dimensions(i));
    }
    //read data array
    std::vector<float> data;
    for (int i = 0; i < imgMes->data_size(); i++) {
        data.push_back(imgMes->data(i));
    }

    return new ImageWrapper(dimensions, data, imgMes->filepath());
}

PlatformInfo* Util::messageToPlatformInfo(const PlatformInfoMessage *platMes) {
    PlatformType type;
    switch (platMes->type()) {
        case PlatformInfoMessage::CPU   : type = PlatformType::CPU;
            break;
        case PlatformInfoMessage::GPU   : type = PlatformType::GPU;
            break;
        case PlatformInfoMessage::FPGA  : type = PlatformType::FPGA;
            break;
            //TODO: exception
        default: throw std::exception();
    }

    return new PlatformInfo(platMes->description(), type, platMes->platformid(), platMes->powerconsumption(),
                            platMes->flops());
}

ImageResult *Util::messageToImageResult(const ImageResultMessage *imgMes) {
    ImageWrapper* img = messageToImageWrapper(&(imgMes->image()));

    std::vector<std::pair<std::string, float>> results;
    for (int i = 0; i < imgMes->classification_size(); i++) {
        results.emplace_back(imgMes->classification(i).name(), imgMes->classification(i).probability());
    }

    std::vector<std::pair<PlatformInfo*, float>> distribution;
    for (int i = 0; i < imgMes->platformdistribution_size(); i++) {
        PlatformInfo* platform = messageToPlatformInfo(&(imgMes->platformdistribution(i).platform()));
        distribution.emplace_back(platform, imgMes->platformdistribution(i).usage());
    }

    return new ImageResult(results, distribution, *img);
}

NetInfo *Util::messageToNetInfo(const NetInfoMessage *net) {
    return new NetInfo(net->name(), net->imagedimension(), net->identifier());
}

std::vector<std::pair<PlatformInfo *, float>> Util::aggregateReplyDistribution(std::vector<ImageResult *> results) {
    auto aggregatePointer = std::vector<std::pair<PlatformInfo*, float>>();

    //for every classification add the platform with new distribution
    for (ImageResult* img : results) {
        for (std::pair<PlatformInfo*, float> dist : img->getCompDistribution()) {
            //Check if the Platform is new
            auto oldDist = std::find_if(aggregatePointer.begin(), aggregatePointer.end(),
                                        [&dist](std::pair<PlatformInfo*, float> newPlat) {
                                            return newPlat.first->getPlatformId() == dist.first->getPlatformId();
                                        });
            //if platform already exists only add float value
            if (oldDist != aggregatePointer.end()) {
                oldDist.operator*().second += (dist.second / results.size());
            } else {
                //insert new platform if it was not found
                std::pair<PlatformInfo*, float> newDist = dist;
                newDist.second = (newDist.second / results.size());
                aggregatePointer.push_back(newDist);
            }
        }
    }
    return aggregatePointer;
}

