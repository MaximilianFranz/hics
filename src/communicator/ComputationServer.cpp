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

#include <Executor.h>
#include "ComputationServer.h"
#include "Util.h"

void ComputationServer::init() {
    fpgaExecutor = new Executor("fpga");
}

Status ComputationServer::classify(::grpc::ServerContext *context, const ::ClassifyRequest *request,
                ::ClassifyReply *reply) {
    std::vector<ImageWrapper*> images;

    for (int i = 0; i < request->images_size(); i++) {
        images.push_back(Util::messageToImageWrapper(&(request->images(i))));
    }

    NetInfo net = *(Util::messageToNetInfo(&(request->net())));

    OperationMode mode;

    switch (request->mode()) {
        case ClassifyRequest::HighPower         : mode = OperationMode::HighPower;
            break;
        case ClassifyRequest::LowPower          : mode = OperationMode::LowPower;
            break;
        case ClassifyRequest::EnergyEfficient   : mode = OperationMode::EnergyEfficient;
            break;
        default:
            throw IllegalArgumentException("Unknown operation mode");
    }

    std::vector<PlatformInfo*> platforms;

    for (int i = 0; i < request->selectedplatforms_size(); i++) {
        platforms.push_back(Util::messageToPlatformInfo(&(request->selectedplatforms(i))));
    }
    //call the classify function in the fpga executor
    std::vector<ImageResult*> results = fpgaExecutor->classify(images, net, mode, platforms);

    //Set the new result in the message reply
    for (auto resultIt : results) {
        ImageResultMessage* newResult = reply->add_results();
        Util::imageResultToMessage(resultIt, newResult);
    }
    return Status::OK;
}

Status
ComputationServer::queryPlatforms(grpc::ServerContext *context, const NullMessage *request, PlatformReply *reply) {
    std::vector<PlatformInfo*> platforms = fpgaExecutor->queryPlatform();

    for (auto platformIt : platforms) {
        PlatformInfoMessage* newPlatform = reply->add_platforms();
        Util::platformInfoToMessage(platformIt, newPlatform);
    }
    return Status::OK;
}

Status
ComputationServer::queryNets(grpc::ServerContext *context, const NullMessage *request, NetInfoReply *reply) {
    std::vector<NetInfo*> nets = fpgaExecutor->queryNets();

    for (auto netIt : nets) {
        NetInfoMessage* newNet = reply->add_nets();
        Util::netInfoToMessage(netIt, newNet);
    }
    return Status::OK;
}

Status
ComputationServer::queryPlatformsRequest(::grpc::ServerContext *context, const ::NullMessage *request,
                                         ::PlatformReply *reply) {
    return ComputationServer::queryPlatforms(context, request, reply);
}

Status ComputationServer::queryNetsRequest(::grpc::ServerContext *context, const ::NullMessage *request,
                                           ::NetInfoReply *reply) {
    return ComputationServer::queryNets(context, request, reply);
}

Status
ComputationServer::classifyRequest(::grpc::ServerContext *context, const ::ClassifyRequest *request,
                                   ::ClassifyReply *response) {
    return ComputationServer::classify(context, request, response);
}
