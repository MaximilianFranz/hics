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

#include <layers/Layer.h>



/**
 * The NetIterator knows how to traverse a neural net.
 * It provides an iterator interface to move on to the next layer after the computations of a layer are computed.
 */
class NetIterator {
protected:
    int index{};
public:

    /**
     * Sets the index to the index of the very first layer in the neural network.
     */
    virtual void first() = 0;

    /**
     * Sets the index to the index of the layer subsequent the current layer.
     */
    virtual void next() = 0;

    /**
     * Checks if the current layer has a subsequent layer.
     *
     * @return true if the current layer has a subsequent layer and false if it is the last layer in the neural network.
     */
    virtual bool hasNext() = 0;

    /**
     * Returns the layer the NetIterator currently tracks.
     *
     * @return the layer with the index that the NetIterator currently tracks.
     */
    virtual Layer* getElement() = 0;
};


