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

class Server {
private:
    ComputationHost* fpgaExecutor;
public:
    void init();

    std::vector<ImageResult *> cassifyRequest(ClientContext &context, ClassifyRequest request, ClassifyReply &reply);
    std::vector<PlatformInfo> queryPlatformsRequest();
    std::vector<NetInfo> queryNetsRequest();
};
