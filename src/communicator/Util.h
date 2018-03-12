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

#include <memory>
#include <string>

#include <ComputationHost.h>

#include "Communicator.grpc.pb.h"
#include "Communicator.pb.h"


namespace Util {

    /**
     * Parses an ImageWrapper to a protobuf ImageWrapper message
     * @param img           ImageWrapper
     * @param messagePtr    protobuf ImageWrapperMessage
     */
    void imageWrapperToMessage(const ImageWrapper* img, ImageWrapperMessage *messagePtr);

    /**
     * Parses a NetInfo object to a protobuf NetInfo message
     * @param net           NetInfo
     * @param messagePtr    protobuf NetInfoMessage
     */
    void netInfoToMessage(NetInfo *net, NetInfoMessage *messagePtr);

    /**
     * Parses a PlatformInfo object to a protobuf PlatformInfo message
     * @param platform      PlatformInfo
     * @param messagePtr    protobuf PlatformInfoMessage
     */
    void platformInfoToMessage(const PlatformInfo* platform, PlatformInfoMessage* messagePtr);

    /**
     * Parses an ImageResult object to a protobuf ImageResult message
     * @param result    ImageResult
     * @param resultPtr protobuf ImageResultMessage
     */
    void imageResultToMessage(const ImageResult* result, ImageResultMessage* resultPtr);

    /**
     * Parses a protobuf ImageWrapper message to an ImageWrapper object
     * @param imgMes    protobuf ImageWrapperMessage
     * @return          ImageWrapper
     */
    ImageWrapper* messageToImageWrapper(const ImageWrapperMessage* imgMes);

    /**
     * Parses a protobuf PlatformInfoMessage to a PlatformInfo object
     * @param platMes   protobuf PlatformInfoMessage
     * @return          PlatformInfo
     */
    PlatformInfo* messageToPlatformInfo(const PlatformInfoMessage* platMes);

    /**
     * Parses a protobuf ImageResultMessage to an ImageResult object
     * @param imgMes    protobuf ImageResultMessage
     * @return          ImageResult
     */
    ImageResult* messageToImageResult(const ImageResultMessage* imgMes);

    /**
     * Parses a protobuf NetInfoMessage to a NetInfo object
     * @param net   protobuf NetInfoMessage
     * @return      NetInfo
     */
    NetInfo* messageToNetInfo(const NetInfoMessage* net);

    /**
     * Since every image is sent as a single classification request, the computation distribution needs to be aggregated
     * in the end
     * @param results   results of all classifications
     * @return          aggregated distribution
     */
    std::vector<std::pair<PlatformInfo*, float>> aggregateReplyDistribution(std::vector<ImageResult*> results);
};
