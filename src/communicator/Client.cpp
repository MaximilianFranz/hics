//
// Created by jallmenroeder on 07/01/18.
//

#include "Client.h"
#include "Util.h"

std::vector<ImageResult*> Client::classify(std::vector<ImageWrapper *> images, NetInfo net, OperationMode mode,
                                           std::vector<PlatformInfo *> selectedPlatforms) {
    ClassifyRequest request;
    ClassifyReply reply;
    ClientContext context;

    for (ImageWrapper* img : images) {
        //Create new ImageWrapperMessage to call classify via grpc
        ImageWrapperMessage* imgMes = request.add_images();
        Util::imageWrapperToMessage(img, imgMes);
    }

    //create and add netInfo message object
    NetInfoMessage* netMes = request.mutable_net();
    Util::netInfoToMessage(net, netMes);

    //set operation mode
    switch (mode) {
        case OperationMode::EnergyEfficient     : request.set_mode(ClassifyRequest::EnergyEfficient);
        case OperationMode::HighPower           : request.set_mode(ClassifyRequest::HighPower);
        case OperationMode::LowPower            : request.set_mode(ClassifyRequest::LowPower);
    }

    //create and add all platforms
    for (PlatformInfo* platform : selectedPlatforms) {
        PlatformInfoMessage* platMes = request.add_selectedplatforms();
        Util::platformInfoToMessage(platform, platMes);
    }
    //Client::stub_.operator*().classify(context, request, reply);
    Status status = Client::stub_.operator*().classify(&context, request, &reply);

    if (status.ok()) {
        std::vector<ImageResult*> results;
        for (int i = 0; i < reply.results_size(); i++) {
            results.push_back(Util::messageToImageResult(&(reply.results(i))));
        }
        return results;
    } else {
        //TODO: specific excepion
        throw std::exception();
    }

}

std::vector<PlatformInfo*> Client::queryPlatform() {
}

std::vector<NetInfo*> Client::queryNets() {
}

//TODO: Cast methods from message objects to c++ and vice versa (see Util::)
