//
// Created by Maximilian Franz on 08.01.18.
//

#include <PlatformInfo.h>
#include "ImageResult.h"



ImageResult::ImageResult(const std::vector<std::pair<std::string, float>> results, ImageWrapper &image)
        : image(image),
          results(results)
{

}

ImageResult::ImageResult(const std::vector<std::pair<std::string, float>> results,
                         const std::vector<std::pair<PlatformInfo, float>> distribution, ImageWrapper &image)
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

const std::vector<std::pair<PlatformInfo, float>> &ImageResult::getCompDistribution() const {
    return compDistribution;
}

void ImageResult::setCompDistribution(const std::vector<std::pair<PlatformInfo, float>> &compDistribution) {
    ImageResult::compDistribution = compDistribution;
}
