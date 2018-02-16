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
