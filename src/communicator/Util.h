//
// Created by jallmenroeder on 30/01/18.
//

#pragma once

#include <memory>
#include <string>

#include <ComputationHost.h>

#include "Communicator.grpc.pb.h"
#include "Communicator.pb.h"


class Util {
public:
    static void imageWrapperToMessage(const ImageWrapper* img, ImageWrapperMessage *messagePtr);
    static void netInfoToMessage(NetInfo *net, NetInfoMessage *messagePtr);
    static void platformInfoToMessage(const PlatformInfo* platform, PlatformInfoMessage* messagePtr);
    static void imageResultToMessage(const ImageResult* result, ImageResultMessage* resultPtr);
    static ImageWrapper* messageToImageWrapper(const ImageWrapperMessage* imgMes);
    static PlatformInfo* messageToPlatformInfo(const PlatformInfoMessage* platMes);
    static ImageResult* messageToImageResult(const ImageResultMessage* imgMes);
    static NetInfo* messageToNetInfo(const NetInfoMessage* net);
};
