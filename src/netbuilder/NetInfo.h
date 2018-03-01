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
