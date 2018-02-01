//
// Created by jallmenroeder on 07/01/18.
//

#pragma once


#include <ImageResult.h>
#include <PlatformInfo.h>
#include <NetInfo.h>
#include <grpc++/channel.h>
#include <ComputationHost.h>

#include "Communicator.pb.h"
#include "Communicator.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

class Server : public Communicator::Service {
private:
    ComputationHost* fpgaExecutor;
    Status classify(::grpc::ServerContext *context, const ::ClassifyRequest *request,
                           ::ClassifyReply *response);
    Status queryPlatforms(::grpc::ServerContext *context, const NullMessage *request, PlatformReply *reply);
    Status queryNets(grpc::ServerContext *context, const NullMessage *request, NetInfoReply *reply);

public:
    void init();

    //Status Communicator::Service::classifyRequest(ClientContext* context, ClassifyRequest* request, ClassifyReply* reply) override ;
    Status queryPlatformsRequest(::grpc::ServerContext *context, const ::NullMessage *request,
                                 ::PlatformReply *reply) override;
    Status queryNetsRequest(::grpc::ServerContext *context, const ::NullMessage *request,
                            ::NetInfoReply *reply) override;
    Status classifyRequest(::grpc::ServerContext *context, const ::ClassifyRequest *request,
                                                  ::ClassifyReply *response) override;
};
