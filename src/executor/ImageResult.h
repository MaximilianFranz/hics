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
#include <map>
#include <wrapper/ImageWrapper.h>
#include <PlatformInfo.h>


class ImageResult {
private:
    ImageWrapper image;
    std::vector<std::pair<std::string, float>> results; //! ordered list of labels and their probabilities
    std::vector<std::pair<PlatformInfo*, float>> compDistribution; //!Shows the distribution of computation on different platforms.
public:
    /**
     * Getter for compDistribution, which Platform computed what in percentages.
     * @return compDistribution
     */
    const std::vector<std::pair<PlatformInfo*, float>> &getCompDistribution() const;

    void setCompDistribution(const std::vector<std::pair<PlatformInfo*, float>> &compDistribution);

    /**\brief Constructor
     *
     * @param results top X
     * @param image
     */
    ImageResult(std::vector<std::pair<std::string, float>> results, ImageWrapper &image);

    ImageResult(std::vector<std::pair<std::string, float>> results,
                std::vector<std::pair<PlatformInfo*, float>> distribution, ImageWrapper &image);

    /**
     *
     * @return path to the image that was classified
     */
    const std::string getImagePath() const;

    /***
     * Return List of result pairs
     * @return
     */
    const std::vector<std::pair<std::string, float>> &getResults() const;

    const ImageWrapper &getImage() const;

};

