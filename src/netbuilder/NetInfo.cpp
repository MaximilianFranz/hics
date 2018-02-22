//
// Created by David Culley on 07.01.18.
//

#include "NetInfo.h"

/**
 * Constructs a net information object from given parameters.
 * @param name name of the neural net
 * @param imageDimension dimensions of the input image (only an int, as input images should be of square shape)
 * @param identifier neural net identifier, basically name written together in lowercase
 */
NetInfo::NetInfo(std::string name, int imageDimension, std::string identifier)
    : name(name), imageDimension(imageDimension), identifier(identifier) {
}

/**
 * Provides the name of the neural net.
 * @return a string which is the neural net's name
 */
std::string NetInfo::getName() {
    return name;
}

/**
 * Provides the dimensions of the images that can be processed by the neural net.
 * @return an integer number (images of square shape), which is the dimension on the neural net's input image
 */
int NetInfo::getImageDimension() {
   return imageDimension;
}

/**
 * Provides the identifier of the neural net.
 * @return a string which is the neural net's name written together in lowercase
 */
std::string NetInfo::getIdentifier() {
    return identifier;
}


