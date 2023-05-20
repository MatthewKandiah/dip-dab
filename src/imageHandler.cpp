#include "imageHandler.hpp"
#include "lodepng/lodepng.h"
#include <iostream>

void ImageHandler::decodePng(const std::string &filename) {
    std::uint32_t error = lodepng::decode(image, width, height, filename);

    if (error) {
        std::cout << "decoder error " << error << ": " << lodepng_error_text(error)
                  << '\n';
    }
}

void ImageHandler::encodePng(const std::string &filename) {
    std::uint32_t error = lodepng::encode(filename, image, width, height);

    if (error) {
        std::cout << "encoder error " << error << ": " << lodepng_error_text(error)
                  << '\n';
    }
}

void ImageHandler::convertToMonochrome() {
    std::vector<std::uint8_t> resultImage;
    for (auto i = 0; i < image.size(); i += 4) {
        const std::uint8_t r = image[i];
        const std::uint8_t g = image[i+1];
        const std::uint8_t b = image[i+2];
        const std::uint8_t alpha = image[i+3];
        const auto grey = static_cast<std::uint8_t>(0.299 * r + 0.587 * g + 0.114 * b);
        resultImage.push_back(grey);
        resultImage.push_back(grey);
        resultImage.push_back(grey);
        resultImage.push_back(alpha);
    }
    image = resultImage;
}

void ImageHandler::invertImage() {
    std::vector<std::uint8_t> resultImage;
    for (auto i = 0; i < image.size(); i += 4) {
        const std::uint8_t r = image[i];
        const std::uint8_t g = image[i+1];
        const std::uint8_t b = image[i+2];
        const std::uint8_t alpha = image[i+3];
        resultImage.push_back(255 - r);
        resultImage.push_back(255 - g);
        resultImage.push_back(255 - b);
        resultImage.push_back(alpha);
    }
    image = resultImage;
}

void ImageHandler::makeOpaque() {
    std::vector<std::uint8_t> resultImage;
    for (auto i = 0; i < image.size(); i += 4) {
        resultImage.push_back(image[i]);
        resultImage.push_back(image[i + 1]);
        resultImage.push_back(image[i + 2]);
        resultImage.push_back(255);
    }
    image = resultImage;
}

// mean blur

// gaussian blur

// edge detection
