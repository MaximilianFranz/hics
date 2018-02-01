//
// Created by jallmenroeder on 07/01/18.
//

#include "Server.h"
#include "Util.h"


Status Server::classify(::grpc::ServerContext *context, const ::ClassifyRequest *request,
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
Server::queryPlatforms(ClientContext *context, NullMessage *request, PlatformReply *reply) {
    return Status::CANCELLED;
}

Status
Server::queryNets(ClientContext *context, NullMessage *request, NetInfoReply *reply) {
    return Status::CANCELLED;
}
