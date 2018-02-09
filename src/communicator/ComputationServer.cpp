//
// Created by jallmenroeder on 07/01/18.
//



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
            //TODO: specific exeption
            throw std::exception();
    }

    std::vector<PlatformInfo*> platforms;

    for (int i = 0; i < request->selectedplatforms_size(); i++) {
        platforms.push_back(Util::messageToPlatformInfo(&(request->selectedplatforms(i))));
    }

    //TODO: find way to include private attribute
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
ComputationServer::queryPlatformsRequest(::grpc::ServerContext *context, const ::NullMessage *request, ::PlatformReply *reply) {
    return ComputationServer::queryPlatforms(context, request, reply);
}

Status ComputationServer::queryNetsRequest(::grpc::ServerContext *context, const ::NullMessage *request, ::NetInfoReply *reply) {
    return ComputationServer::queryNets(context, request, reply);
}

Status
ComputationServer::classifyRequest(::grpc::ServerContext *context, const ::ClassifyRequest *request, ::ClassifyReply *response) {
    return ComputationServer::classify(context, request, response);
}