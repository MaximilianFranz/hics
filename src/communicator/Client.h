//
// Created by jallmenroeder on 07/01/18.
//

#pragma once

#include <grpc/grpc.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <grpc++/security/server_credentials.h>
#include <grpc++/grpc++.h>
#include <memory>
#include <string>

#include <ComputationHost.h>

#include "Communicator.grpc.pb.h"
#include "Communicator.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

class Client : public ComputationHost {
private:
    std::unique_ptr<Communicator::Stub> stub_;
    std::string ComputationHost::name;
public:
    explicit Client(std::shared_ptr<Channel> channel);
    Client(std::string name, std::shared_ptr<Channel> channel);

    std::vector<ImageResult*> classify(std::vector<ImageWrapper*> images, NetInfo net, OperationMode mode,
                                      std::vector<PlatformInfo*> selectedPlatforms) override;

    std::vector<PlatformInfo*> queryPlatform() override;
    std::vector<NetInfo*> queryNets() override;
};
