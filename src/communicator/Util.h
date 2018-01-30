//
// Created by jallmenroeder on 30/01/18.
//

#pragma once

#include <memory>
#include <string>

#include <ComputationHost.h>

#include "Messages/Communicator.grpc.pb.h"
#include "Messages/Communicator.pb.h"


class Util {
public:
    static void imageWrapperToMessage(const ImageWrapper* img, ImageWrapperMessage *messagePtr);
    static void netInfoToMessage(NetInfo net, NetInfoMessage *messagePtr);
    static void platformInfoToMessage(const PlatformInfo* platform, PlatformInfoMessage* messagePtr);
    static ImageWrapper* messageToImageWrapper(const ImageWrapperMessage* imgMes);
    static PlatformInfo* messageToPlatformInfo(const PlatformInfoMessage* platMes);
    static ImageResult* messageToImageResult(const ImageResultMessage* imgMes);
};
