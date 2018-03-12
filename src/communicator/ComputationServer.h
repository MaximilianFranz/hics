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

class ComputationServer : public Communicator::Service {
private:
    ComputationHost* fpgaExecutor;

    /**
     * Parses the grpc message to c++ objects and calls the corresponding executor function
     * @param context
     * @param request
     * @param response
     * @return  status if the grpc call went successful
     */
    Status classify(::grpc::ServerContext *context, const ::ClassifyRequest *request,
                           ::ClassifyReply *response);

    /**
     * Parses the grpc message to c++ objects and calls the corresponding executor function
     * @param context
     * @param request
     * @param response
     * @return  status if the grpc call went successful
     */
    Status queryPlatforms(::grpc::ServerContext *context, const NullMessage *request, PlatformReply *reply);

    /**
     * Parses the grpc message to c++ objects and calls the corresponding executor function
     * @param context
     * @param request
     * @param response
     * @return  status if the grpc call went successful
     */
    Status queryNets(grpc::ServerContext *context, const NullMessage *request, NetInfoReply *reply);

public:

    /**
     * Initialises the server
     */
    void init();

    Status queryPlatformsRequest(::grpc::ServerContext *context, const ::NullMessage *request,
                                 ::PlatformReply *reply) override;
    Status queryNetsRequest(::grpc::ServerContext *context, const ::NullMessage *request,
                            ::NetInfoReply *reply) override;
    Status classifyRequest(::grpc::ServerContext *context, const ::ClassifyRequest *request,
                                                  ::ClassifyReply *response) override;
};
