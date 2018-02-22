//
// Created by David Culley on 07.01.18.
//

#pragma once

#include <string>

class NetInfo {
private:
    std::string name;
    int imageDimension;
    std::string identifier;


public:
    /**
    * Constructs a net information object from given parameters.
     *
    * @param name name of the neural net
    * @param imageDimension dimensions of the input image (only an int, as input images should be of square shape)
    * @param identifier neural net identifier, basically name written together in lowercase
    */
    NetInfo(std::string name, int imageDimension, std::string identifier);

    /**
    * Provides the name of the neural net.
     *
    * @return a string which is the neural net's name
    */
    std::string getName();

    /**
    * Provides the dimensions of the images that can be processed by the neural net.
     *
    * @return an integer number (images of square shape), which is the dimension on the neural net's input image
    */
    int getImageDimension();

    /**
    * Provides the identifier of the neural net.
     * 
    * @return a string which is the neural net's name written together in lowercase
    */
    std::string getIdentifier();

};
