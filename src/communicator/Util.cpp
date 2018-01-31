//
// Created by jallmenroeder on 30/01/18.
//

#include "Util.h"

void Util::imageWrapperToMessage(const ImageWrapper *img, ImageWrapperMessage *messagePtr) {
    messagePtr->set_filepath(img->getFilepath());
    for (int dim : img->getDimensions()) {
        messagePtr->add_dimensions(dim);
    }

    //Every pixel in the float array has to be added individually
    for (float pixel : img->getData()) {
        messagePtr->add_data(pixel);
    }
}

void Util::netInfoToMessage(NetInfo net, NetInfoMessage *messagePtr) {
    messagePtr->set_name(net.getName());
    messagePtr->set_identifier(net.getIdentifier());
    messagePtr->set_imagedimension(net.getImageDimension());
}

void Util::platformInfoToMessage(const PlatformInfo *platform, PlatformInfoMessage *messagePtr) {
    messagePtr->set_description(platform->getDescription());
    switch (platform->getType()) {
        case PlatformType::CPU  : messagePtr->set_type(PlatformInfoMessage::CPU);
            break;
        case PlatformType::FPGA : messagePtr->set_type(PlatformInfoMessage::FPGA);
            break;
        case PlatformType::GPU  : messagePtr->set_type(PlatformInfoMessage::GPU);
            break;
    }
    messagePtr->set_platformid(platform->getPlatformId());
    messagePtr->set_powerconsumption(platform->getPowerConsumption());
    messagePtr->set_flops(platform->getFlops());
}

ImageWrapper* Util::messageToImageWrapper(const ImageWrapperMessage *imgMes) {
    //read dimensions
    std::vector<int> dimensions;
    for (int i = 0; i < imgMes->dimensions_size(); i++) {
        dimensions.push_back(imgMes->dimensions(i));
    }
    //read data array
    std::vector<float> data;
    for (int i = 0; i < imgMes->data_size(); i++) {
        data.push_back(imgMes->data(i));
    }

    return new ImageWrapper(dimensions, data, imgMes->filepath());
}

PlatformInfo* Util::messageToPlatformInfo(const PlatformInfoMessage *platMes) {
    PlatformType type;
    switch (platMes->type()) {
        case PlatformInfoMessage::CPU   : type = PlatformType::CPU;
            break;
        case PlatformInfoMessage::GPU   : type = PlatformType::GPU;
            break;
        case PlatformInfoMessage::FPGA  : type = PlatformType::FPGA;
            break;
            //TODO: exception
        default: throw std::exception();
    }

    return new PlatformInfo(platMes->description(), type, platMes->platformid(), platMes->powerconsumption(),
                            platMes->flops());
}

ImageResult *Util::messageToImageResult(const ImageResultMessage *imgMes) {
    ImageWrapper* img = messageToImageWrapper(&(imgMes->image()));

    std::vector<std::pair<std::string, float>> results;
    for (int i = 0; i < imgMes->classification_size(); i++) {
        results.emplace_back(imgMes->classification(i).name(), imgMes->classification(i).probability());
    }

    std::vector<std::pair<PlatformInfo, float>> distribution;
    for (int i = 0; i < imgMes->platformdistribution_size(); i++) {
        PlatformInfo* platform = messageToPlatformInfo(&(imgMes->platformdistribution(i).platform()));
        distribution.emplace_back(*platform, imgMes->platformdistribution(i).usage());
    }

    return new ImageResult(results, distribution, *img);
}
