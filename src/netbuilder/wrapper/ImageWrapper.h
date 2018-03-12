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
#include "Wrapper.h"

class ImageWrapper : public Wrapper {
private:
    std::string filepath; //! filepath to the image this ImageWrapper represents

public:
    /**
     * Create empty ImageWrapper
     *
     * @param numDimensions
     * @param dimensions
     * @param filepath
     * @see Wrapper
     */
    explicit ImageWrapper(std::vector<int> &dimensions, std::string filepath);
    /**
     * Create ImageWrapper from existing data vector
     *
     * @param numDimensions
     * @param dimensions
     * @param data
     * @param filepath
     */
    explicit ImageWrapper(std::vector<int> dimensions, std::vector<float> &data, std::string filepath);

    /**
     * Get path to the original image this wrapper represents
     *
     * @return path to the image on the hard drive
     */
    const std::string getFilepath() const;

};
