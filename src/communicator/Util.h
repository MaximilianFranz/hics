//
// Created by jallmenroeder on 30/01/18.
//

#pragma once

#include <memory>
#include <string>

#include <ComputationHost.h>

#include "Communicator.grpc.pb.h"
#include "Communicator.pb.h"


namespace Util {
    void imageWrapperToMessage(const ImageWrapper* img, ImageWrapperMessage *messagePtr);
    void netInfoToMessage(NetInfo *net, NetInfoMessage *messagePtr);
    void platformInfoToMessage(const PlatformInfo* platform, PlatformInfoMessage* messagePtr);
    void imageResultToMessage(const ImageResult* result, ImageResultMessage* resultPtr);
    ImageWrapper* messageToImageWrapper(const ImageWrapperMessage* imgMes);
    PlatformInfo* messageToPlatformInfo(const PlatformInfoMessage* platMes);
    ImageResult* messageToImageResult(const ImageResultMessage* imgMes);
    NetInfo* messageToNetInfo(const NetInfoMessage* net);
};
