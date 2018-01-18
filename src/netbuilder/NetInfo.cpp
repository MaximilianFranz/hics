//
// Created by David Culley on 07.01.18.
//

#include "NetInfo.h"
#include "../NotImplementedException.h"

NetInfo::NetInfo(std::string name, int imageDimension)
    : name(name), imageDimension(imageDimension){
    //throw NotImplementedException();
}

std::string NetInfo::getName() {
    return name;
}

int NetInfo::getImageDimension() {
   return imageDimension;
}

std::string NetInfo::getIdentifier() {
    throw NotImplementedException();
}
