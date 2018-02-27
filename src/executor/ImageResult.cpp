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

#include <PlatformInfo.h>
#include "ImageResult.h"



ImageResult::ImageResult(const std::vector<std::pair<std::string, float>> results, ImageWrapper &image)
        : image(image),
          results(results)
{

}

ImageResult::ImageResult(const std::vector<std::pair<std::string, float>> results,
                         const std::vector<std::pair<PlatformInfo*, float>> distribution, ImageWrapper &image)
        : results(results),
          compDistribution(distribution),
          image(image)
{

}

const std::vector<std::pair<std::string, float>> &ImageResult::getResults() const {
    return results;
}

const std::string ImageResult::getImagePath() const {
    return image.getFilepath();
}

const std::vector<std::pair<PlatformInfo*, float>> &ImageResult::getCompDistribution() const {
    return compDistribution;
}

void ImageResult::setCompDistribution(const std::vector<std::pair<PlatformInfo*, float>> &compDistribution) {
    ImageResult::compDistribution = compDistribution;
}

const ImageWrapper &ImageResult::getImage() const {
    return image;
}
