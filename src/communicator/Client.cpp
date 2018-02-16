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

#include "Client.h"
#include "Util.h"

Client::Client(std::shared_ptr<Channel> channel) : stub_(Communicator::NewStub(channel)) {}
Client::Client(std::string name, std::shared_ptr<Channel> channel) : stub_(Communicator::NewStub(channel)) {
    ComputationHost::name = name;
}

std::vector<ImageResult*> Client::classify(std::vector<ImageWrapper *> images, NetInfo net, OperationMode mode,
                                           std::vector<PlatformInfo *> selectedPlatforms) {
    ClassifyRequest request;
    ClassifyReply reply;
    ClientContext context;

    for (ImageWrapper* img : images) {
        //Create new ImageWrapperMessage to call classify via grpc
        ImageWrapperMessage* imgMes = request.add_images();
        Util::imageWrapperToMessage(img, imgMes);
    }

    //create and add netInfo message object
    NetInfoMessage* netMes = request.mutable_net();
    Util::netInfoToMessage(&net, netMes);

    //set operation mode
    switch (mode) {
        case OperationMode::EnergyEfficient     : request.set_mode(ClassifyRequest::EnergyEfficient);
        case OperationMode::HighPower           : request.set_mode(ClassifyRequest::HighPower);
        case OperationMode::LowPower            : request.set_mode(ClassifyRequest::LowPower);
    }

    //create and add all platforms
    for (PlatformInfo* platform : selectedPlatforms) {
        PlatformInfoMessage* platMes = request.add_selectedplatforms();
        Util::platformInfoToMessage(platform, platMes);
    }
    //Client::stub_.operator*().classify(context, request, reply);
    Status status = Client::stub_.operator*().classifyRequest(&context, request, &reply);

    if (status.ok()) {
        std::vector<ImageResult*> results;
        for (int i = 0; i < reply.results_size(); i++) {
            results.push_back(Util::messageToImageResult(&(reply.results(i))));
        }
        return results;
    } else {
        //TODO: specific excepion
        throw std::exception();
    }

}

std::vector<PlatformInfo*> Client::queryPlatform() {
    NullMessage request;
    PlatformReply reply;
    ClientContext context;

    Status status = Client::stub_.operator*().queryPlatformsRequest(&context, request, &reply);

    if (status.ok()) {
        std::vector<PlatformInfo*> platforms;
        for (int i = 0; i < reply.platforms_size(); i++) {
            platforms.push_back(Util::messageToPlatformInfo(&(reply.platforms(i))));
        }
        return platforms;
    } else {
        //TODO: specific exeption
        throw std::exception();
    }

}

std::vector<NetInfo*> Client::queryNets() {
    NullMessage request;
    NetInfoReply reply;
    ClientContext context;

    Status status = Client::stub_.operator*().queryNetsRequest(&context, request, &reply);

    if (status.ok()) {
        std::vector<NetInfo*> nets;
        for (int i = 0; i < reply.nets_size(); i++) {
            nets.push_back(Util::messageToNetInfo(&(reply.nets(i))));
        }
        return nets;
    } else {
        throw new std::exception();
    }
}
