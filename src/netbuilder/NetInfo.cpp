//
// Created by David Culley on 07.01.18.
//

#include "NetInfo.h"


NetInfo::NetInfo(std::string name, int imageDimension, std::string identifier)
    : name(name), imageDimension(imageDimension), identifier(identifier) {
    //
}

std::string NetInfo::getName() {
    return name;
}

int NetInfo::getImageDimension() {
   return imageDimension;
}

std::string NetInfo::getIdentifier() {
    return identifier;
}


