//
// Created by Maximilian Franz on 08.01.18.
//

#include "ImageResult.h"



ImageResult::ImageResult(const std::vector<std::pair<std::string, float>> results, ImageWrapper &image)
        : image(image),
          results(results)
{

}

const std::vector<std::pair<std::string, float>> &ImageResult::getResults() const {
    return results;
}

const std::string ImageResult::getImagePath() const {
    return image.getFilepath();
}
